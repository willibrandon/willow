use criterion::{black_box, criterion_group, criterion_main, Criterion, BenchmarkId};
use willow::{PatternMatcher, WillowScanner, BufferId, BufferVersion};

fn generate_text(size: usize, todo_density: f32) -> String {
    let mut text = String::new();
    let keywords = ["TODO", "FIXME", "HACK", "NOTE", "BUG", "OPTIMIZE", "SECURITY"];
    
    for i in 0..size {
        let should_have_todo = (i as f32 / size as f32) < todo_density;
        
        if should_have_todo && i % 10 == 0 {
            let keyword = keywords[i % keywords.len()];
            text.push_str(&format!("// {}: Task number {}\n", keyword, i));
        } else if i % 5 == 0 {
            text.push_str(&format!("/* Block comment {}\n   with multiple lines */\n", i));
        } else {
            text.push_str(&format!("// Regular comment {}\n", i));
        }
        
        // Add some code lines too
        if i % 20 == 0 {
            text.push_str(&format!("fn function_{}() {{\n    let x = {};\n}}\n", i, i));
        }
    }
    text
}

fn generate_unicode_text(size: usize) -> String {
    let mut text = String::new();
    let unicode_messages = [
        "修复这个问题 🔧",
        "Ñoño está roto 🇪🇸", 
        "Временное решение 🇷🇺",
        "日本語のコメント 🇯🇵",
        "Πρόβλημα εδώ 🇬🇷",
        "최적화가 필요함 🇰🇷",
    ];
    
    for i in 0..size {
        if i % 10 == 0 {
            let message = unicode_messages[i % unicode_messages.len()];
            text.push_str(&format!("// TODO: {}\n", message));
        } else {
            text.push_str(&format!("// Regular comment {}\n", i));
        }
    }
    text
}

fn bench_pattern_matching_sizes(c: &mut Criterion) {
    let matcher = PatternMatcher::default();
    
    let sizes = [100, 1000, 5000, 10000];
    let mut group = c.benchmark_group("pattern_matching_sizes");
    
    for size in sizes.iter() {
        let text = generate_text(*size, 0.1); // 10% of lines have TODOs
        group.bench_with_input(
            BenchmarkId::new("lines", size),
            &text,
            |b, text| {
                b.iter(|| {
                    matcher.find_all(black_box(text))
                });
            },
        );
    }
    group.finish();
}

fn bench_todo_density(c: &mut Criterion) {
    let matcher = PatternMatcher::default();
    let size = 1000;
    
    let densities = [0.0, 0.05, 0.1, 0.2, 0.5];
    let mut group = c.benchmark_group("todo_density");
    
    for density in densities.iter() {
        let text = generate_text(size, *density);
        group.bench_with_input(
            BenchmarkId::new("density", (density * 100.0) as u32),
            &text,
            |b, text| {
                b.iter(|| {
                    matcher.find_all(black_box(text))
                });
            },
        );
    }
    group.finish();
}

fn bench_unicode_handling(c: &mut Criterion) {
    let matcher = PatternMatcher::default();
    
    let sizes = [100, 1000, 5000];
    let mut group = c.benchmark_group("unicode_handling");
    
    for size in sizes.iter() {
        let text = generate_unicode_text(*size);
        group.bench_with_input(
            BenchmarkId::new("unicode_lines", size),
            &text,
            |b, text| {
                b.iter(|| {
                    matcher.find_all(black_box(text))
                });
            },
        );
    }
    group.finish();
}

fn bench_scanner_with_cache(c: &mut Criterion) {
    let mut group = c.benchmark_group("scanner_cache");
    
    let text = generate_text(1000, 0.1);
    let buffer_id = BufferId::new(1);
    let version = BufferVersion::new(1);
    
    group.bench_function("first_scan", |b| {
        b.iter(|| {
            let mut scanner = WillowScanner::default();
            scanner.scan_buffer(buffer_id, version, black_box(&text))
        });
    });
    
    group.bench_function("cached_scan", |b| {
        let mut scanner = WillowScanner::default();
        // Prime the cache
        scanner.scan_buffer(buffer_id, version, &text);
        
        b.iter(|| {
            scanner.scan_buffer(buffer_id, version, black_box(&text))
        });
    });
    
    group.finish();
}

fn bench_different_patterns(c: &mut Criterion) {
    let mut group = c.benchmark_group("pattern_types");
    
    let todo_text = generate_text_with_pattern(1000, "TODO");
    let fixme_text = generate_text_with_pattern(1000, "FIXME");
    let mixed_text = generate_text(1000, 0.1);
    
    let matcher = PatternMatcher::default();
    
    group.bench_function("todo_only", |b| {
        b.iter(|| matcher.find_all(black_box(&todo_text)));
    });
    
    group.bench_function("fixme_only", |b| {
        b.iter(|| matcher.find_all(black_box(&fixme_text)));
    });
    
    group.bench_function("mixed_patterns", |b| {
        b.iter(|| matcher.find_all(black_box(&mixed_text)));
    });
    
    group.finish();
}

fn generate_text_with_pattern(size: usize, pattern: &str) -> String {
    let mut text = String::new();
    for i in 0..size {
        if i % 10 == 0 {
            text.push_str(&format!("// {}: Message {}\n", pattern, i));
        } else {
            text.push_str(&format!("// Regular comment {}\n", i));
        }
    }
    text
}

fn bench_edge_cases(c: &mut Criterion) {
    let matcher = PatternMatcher::default();
    let mut group = c.benchmark_group("edge_cases");
    
    // Long lines
    let long_line_text = format!("// TODO: {}\n", "x".repeat(1000));
    group.bench_function("long_lines", |b| {
        b.iter(|| matcher.find_all(black_box(&long_line_text)));
    });
    
    // Many short lines
    let many_short_lines = (0..1000)
        .map(|i| format!("// TODO: {}\n", i))
        .collect::<String>();
    group.bench_function("many_short_lines", |b| {
        b.iter(|| matcher.find_all(black_box(&many_short_lines)));
    });
    
    // No matches
    let no_matches = "// Regular comment\n".repeat(1000);
    group.bench_function("no_matches", |b| {
        b.iter(|| matcher.find_all(black_box(&no_matches)));
    });
    
    // All matches
    let all_matches = "// TODO: item\n".repeat(1000);
    group.bench_function("all_matches", |b| {
        b.iter(|| matcher.find_all(black_box(&all_matches)));
    });
    
    group.finish();
}

fn bench_memory_usage(c: &mut Criterion) {
    let mut group = c.benchmark_group("memory_usage");
    
    // Large result set
    let large_result_text = "// TODO: item\n".repeat(10000);
    let matcher = PatternMatcher::default();
    
    group.bench_function("large_result_set", |b| {
        b.iter(|| {
            let results = matcher.find_all(black_box(&large_result_text));
            // Force the results to be used so they're not optimized away
            black_box(results.len())
        });
    });
    
    group.finish();
}

criterion_group!(
    benches,
    bench_pattern_matching_sizes,
    bench_todo_density,
    bench_unicode_handling,
    bench_scanner_with_cache,
    bench_different_patterns,
    bench_edge_cases,
    bench_memory_usage
);

criterion_main!(benches);