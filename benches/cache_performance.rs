use criterion::{black_box, criterion_group, criterion_main, Criterion, BenchmarkId};
use willow::{ResultCache, BufferId, BufferVersion, PatternMatcher, TodoMatch, HighlightStyle};

fn create_test_todos(count: usize) -> Vec<TodoMatch> {
    (0..count)
        .map(|i| TodoMatch {
            keyword: "TODO".to_string(),
            message: format!("Test message {}", i),
            start: i * 20,
            end: i * 20 + 10,
            priority: 1,
            style: HighlightStyle::Info,
        })
        .collect()
}

fn bench_cache_operations(c: &mut Criterion) {
    let mut group = c.benchmark_group("cache_operations");
    
    let items = create_test_todos(100);
    let buffer_id = BufferId::new(1);
    let version = BufferVersion::new(1);
    
    group.bench_function("insert", |b| {
        b.iter(|| {
            let mut cache = ResultCache::new(1000);
            cache.insert(buffer_id, version, black_box(items.clone()));
        });
    });
    
    group.bench_function("get_hit", |b| {
        let mut cache = ResultCache::new(1000);
        cache.insert(buffer_id, version, items.clone());
        
        b.iter(|| {
            cache.get(buffer_id, version);
        });
    });
    
    group.bench_function("get_miss", |b| {
        let mut cache = ResultCache::new(1000);
        let miss_version = BufferVersion::new(999);
        
        b.iter(|| {
            cache.get(buffer_id, miss_version);
        });
    });
    
    group.finish();
}

fn bench_cache_sizes(c: &mut Criterion) {
    let mut group = c.benchmark_group("cache_sizes");
    let items = create_test_todos(10);
    
    let cache_sizes = [10, 100, 1000, 5000];
    
    for size in cache_sizes.iter() {
        group.bench_with_input(
            BenchmarkId::new("insert_until_full", size),
            size,
            |b, &size| {
                b.iter(|| {
                    let mut cache = ResultCache::new(size);
                    for i in 0..size {
                        let buffer_id = BufferId::new(i as u64);
                        let version = BufferVersion::new(1);
                        cache.insert(buffer_id, version, items.clone());
                    }
                });
            },
        );
    }
    
    group.finish();
}

fn bench_cache_eviction(c: &mut Criterion) {
    let mut group = c.benchmark_group("cache_eviction");
    let items = create_test_todos(10);
    
    group.bench_function("eviction_pressure", |b| {
        let cache_size = 100;
        let insert_count = 200; // 2x cache size to force evictions
        
        b.iter(|| {
            let mut cache = ResultCache::new(cache_size);
            for i in 0..insert_count {
                let buffer_id = BufferId::new(i as u64);
                let version = BufferVersion::new(1);
                cache.insert(buffer_id, version, items.clone());
            }
            black_box(cache.len()); // Ensure cache is used
        });
    });
    
    group.finish();
}

fn bench_cache_access_patterns(c: &mut Criterion) {
    let mut group = c.benchmark_group("cache_access_patterns");
    let items = create_test_todos(50);
    let cache_size = 100;
    
    // Sequential access pattern
    group.bench_function("sequential_access", |b| {
        let mut cache = ResultCache::new(cache_size);
        
        // Pre-populate cache
        for i in 0..cache_size {
            let buffer_id = BufferId::new(i as u64);
            let version = BufferVersion::new(1);
            cache.insert(buffer_id, version, items.clone());
        }
        
        b.iter(|| {
            for i in 0..cache_size {
                let buffer_id = BufferId::new(i as u64);
                let version = BufferVersion::new(1);
                black_box(cache.get(buffer_id, version));
            }
        });
    });
    
    // Random access pattern
    group.bench_function("random_access", |b| {
        let mut cache = ResultCache::new(cache_size);
        
        // Pre-populate cache
        for i in 0..cache_size {
            let buffer_id = BufferId::new(i as u64);
            let version = BufferVersion::new(1);
            cache.insert(buffer_id, version, items.clone());
        }
        
        // Create a pseudo-random access pattern
        let access_pattern: Vec<_> = (0..cache_size)
            .map(|i| (i * 47) % cache_size) // Simple pseudo-random
            .collect();
        
        b.iter(|| {
            for &i in &access_pattern {
                let buffer_id = BufferId::new(i as u64);
                let version = BufferVersion::new(1);
                black_box(cache.get(buffer_id, version));
            }
        });
    });
    
    group.finish();
}

fn bench_version_management(c: &mut Criterion) {
    let mut group = c.benchmark_group("version_management");
    let items = create_test_todos(20);
    let buffer_id = BufferId::new(1);
    
    group.bench_function("version_updates", |b| {
        b.iter(|| {
            let mut cache = ResultCache::new(100);
            
            // Simulate rapid version updates for same buffer
            for version in 0..50 {
                let version = BufferVersion::new(version);
                cache.insert(buffer_id, version, items.clone());
            }
        });
    });
    
    group.bench_function("multi_version_access", |b| {
        let mut cache = ResultCache::new(100);
        
        // Pre-populate with multiple versions
        for version in 0..20 {
            let version = BufferVersion::new(version);
            cache.insert(buffer_id, version, items.clone());
        }
        
        b.iter(|| {
            for version in 0..20 {
                let version = BufferVersion::new(version);
                black_box(cache.get(buffer_id, version));
            }
        });
    });
    
    group.finish();
}

fn bench_result_sizes(c: &mut Criterion) {
    let mut group = c.benchmark_group("result_sizes");
    let buffer_id = BufferId::new(1);
    let version = BufferVersion::new(1);
    
    let sizes = [1, 10, 100, 500, 1000];
    
    for size in sizes.iter() {
        let items = create_test_todos(*size);
        
        group.bench_with_input(
            BenchmarkId::new("insert_size", size),
            &items,
            |b, items| {
                b.iter(|| {
                    let mut cache = ResultCache::new(100);
                    cache.insert(buffer_id, version, black_box(items.clone()));
                });
            },
        );
        
        group.bench_with_input(
            BenchmarkId::new("get_size", size),
            &items,
            |b, items| {
                let mut cache = ResultCache::new(100);
                cache.insert(buffer_id, version, items.clone());
                
                b.iter(|| {
                    black_box(cache.get(buffer_id, version));
                });
            },
        );
    }
    
    group.finish();
}

fn bench_buffer_invalidation(c: &mut Criterion) {
    let mut group = c.benchmark_group("buffer_invalidation");
    let items = create_test_todos(50);
    
    group.bench_function("invalidate_single_buffer", |b| {
        b.iter(|| {
            let mut cache = ResultCache::new(1000);
            let target_buffer = BufferId::new(500);
            
            // Fill cache with many buffers
            for i in 0..1000 {
                let buffer_id = BufferId::new(i);
                let version = BufferVersion::new(1);
                cache.insert(buffer_id, version, items.clone());
            }
            
            // Invalidate one buffer
            cache.invalidate_buffer(target_buffer);
        });
    });
    
    group.bench_function("invalidate_many_versions", |b| {
        b.iter(|| {
            let mut cache = ResultCache::new(1000);
            let target_buffer = BufferId::new(1);
            
            // Insert many versions of the same buffer
            for version in 0..100 {
                let version = BufferVersion::new(version);
                cache.insert(target_buffer, version, items.clone());
            }
            
            // Fill with other buffers too
            for i in 2..1000 {
                let buffer_id = BufferId::new(i);
                let version = BufferVersion::new(1);
                cache.insert(buffer_id, version, items.clone());
            }
            
            // Invalidate the buffer with many versions
            cache.invalidate_buffer(target_buffer);
        });
    });
    
    group.finish();
}

fn bench_cache_statistics(c: &mut Criterion) {
    let mut group = c.benchmark_group("cache_statistics");
    let items = create_test_todos(10);
    let cache_size = 100;
    
    group.bench_function("stats_tracking_overhead", |b| {
        let mut cache = ResultCache::new(cache_size);
        let buffer_id = BufferId::new(1);
        let version = BufferVersion::new(1);
        
        // Pre-populate for mix of hits and misses
        cache.insert(buffer_id, version, items.clone());
        
        b.iter(|| {
            // Mix of operations to test stats overhead
            black_box(cache.get(buffer_id, version)); // Hit
            black_box(cache.get(BufferId::new(999), version)); // Miss
            black_box(cache.stats().hit_ratio()); // Stats calculation
        });
    });
    
    group.finish();
}

criterion_group!(
    benches,
    bench_cache_operations,
    bench_cache_sizes,
    bench_cache_eviction,
    bench_cache_access_patterns,
    bench_version_management,
    bench_result_sizes,
    bench_buffer_invalidation,
    bench_cache_statistics
);

criterion_main!(benches);