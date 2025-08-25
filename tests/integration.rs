use std::fs;
use std::path::Path;
use willow::{scan_file, PatternMatcher, WillowScanner, BufferId, BufferVersion};

fn load_fixture(name: &str) -> String {
    let path = Path::new("tests/fixtures/sample_code").join(name);
    fs::read_to_string(path).expect(&format!("Failed to load fixture: {}", name))
}

fn load_edge_case_fixture(name: &str) -> String {
    let path = Path::new("tests/fixtures/edge_cases").join(name);
    fs::read_to_string(path).expect(&format!("Failed to load edge case fixture: {}", name))
}

#[test]
fn test_rust_file_scanning() {
    let content = load_fixture("rust_todos.rs");
    let results = scan_file(&content, "rust");
    
    // Verify we found expected TODOs
    assert!(!results.is_empty(), "Should find TODO items in Rust file");
    
    let keywords: std::collections::HashSet<_> = results.iter().map(|r| &r.keyword).collect();
    
    // Check that we found the main keywords
    assert!(keywords.contains(&"TODO".to_string()));
    assert!(keywords.contains(&"FIXME".to_string()));
    assert!(keywords.contains(&"HACK".to_string()));
    assert!(keywords.contains(&"NOTE".to_string()));
    assert!(keywords.contains(&"BUG".to_string()));
    assert!(keywords.contains(&"OPTIMIZE".to_string()));
    assert!(keywords.contains(&"DEPRECATED".to_string()));
    assert!(keywords.contains(&"SECURITY".to_string()));
    
    // Verify messages are captured
    let has_message = results.iter().any(|r| !r.message.is_empty());
    assert!(has_message, "Should capture TODO messages");
    
    // Check for specific expected items
    let todo_main = results.iter().find(|r| r.message.contains("Implement the main function"));
    assert!(todo_main.is_some(), "Should find 'Implement the main function' TODO");
    
    let fixme_broken = results.iter().find(|r| r.message.contains("This is broken"));
    assert!(fixme_broken.is_some(), "Should find 'This is broken' FIXME");
}

#[test]
fn test_python_file_scanning() {
    let content = load_fixture("python_todos.py");
    let results = scan_file(&content, "python");
    
    assert!(!results.is_empty(), "Should find TODO items in Python file");
    
    // Python specific: should handle # comments and docstrings
    let has_hash_comment = results.iter().any(|r| r.message.contains("Add error handling"));
    assert!(has_hash_comment, "Should handle # comments");
    
    let has_docstring_todo = results.iter().any(|r| r.message.contains("Add documentation"));
    assert!(has_docstring_todo, "Should handle TODOs in docstrings");
    
    // Unicode support test
    let has_unicode = results.iter().any(|r| r.message.contains("支持Unicode") || r.message.contains("修复这个问题"));
    assert!(has_unicode, "Should handle Unicode in TODO messages");
}

#[test]
fn test_javascript_file_scanning() {
    let content = load_fixture("javascript_todos.js");
    let results = scan_file(&content, "javascript");
    
    assert!(!results.is_empty(), "Should find TODO items in JavaScript file");
    
    // Should handle both // and /* */ comments
    let has_line_comment = results.iter().any(|r| r.message.contains("Convert to TypeScript"));
    assert!(has_line_comment, "Should handle // comments");
    
    let has_block_comment = results.iter().any(|r| r.message.contains("Refactor this mess"));
    assert!(has_block_comment, "Should handle /* */ comments");
    
    // Check for class-related TODOs
    let has_class_todo = results.iter().any(|r| r.message.contains("Add JSDoc comments"));
    assert!(has_class_todo, "Should find TODOs in class methods");
}

#[test]
fn test_edge_case_nested_comments() {
    let content = load_edge_case_fixture("nested_comments.rs");
    let results = scan_file(&content, "rust");
    
    assert!(!results.is_empty(), "Should handle nested comments");
    
    // Should not include comment markers in messages
    for result in &results {
        assert!(!result.message.contains("*/"), "Messages should not contain closing comment markers");
        assert!(!result.message.contains("/*"), "Messages should not contain opening comment markers");
    }
    
    // Should find TODOs in nested structures
    let has_nested_todo = results.iter().any(|r| r.keyword == "TODO");
    assert!(has_nested_todo, "Should find TODOs in nested comments");
}

#[test]
fn test_unicode_edge_cases() {
    let content = load_edge_case_fixture("unicode_todos.py");
    let results = scan_file(&content, "python");
    
    assert!(!results.is_empty(), "Should handle Unicode edge cases");
    
    // Test various Unicode scenarios
    let unicode_messages: Vec<_> = results.iter().map(|r| &r.message).collect();
    
    // Should handle Chinese characters
    let has_chinese = unicode_messages.iter().any(|msg| msg.contains("修复"));
    assert!(has_chinese, "Should handle Chinese characters");
    
    // Should handle emojis
    let has_emoji = unicode_messages.iter().any(|msg| msg.contains("🔧") || msg.contains("🚀"));
    assert!(has_emoji, "Should handle emoji characters");
    
    // Should handle mixed scripts
    let has_mixed_scripts = unicode_messages.iter().any(|msg| {
        msg.contains("Русский") && (msg.contains("中文") || msg.contains("Español"))
    });
    assert!(has_mixed_scripts, "Should handle mixed script text");
}

#[test]
fn test_scanner_performance() {
    let mut scanner = WillowScanner::default();
    let buffer_id = BufferId::new(1);
    let version = BufferVersion::new(1);
    
    // Load a reasonably sized file
    let content = load_fixture("rust_todos.rs");
    
    // First scan should populate cache
    let start = std::time::Instant::now();
    let results1 = scanner.scan_buffer(buffer_id, version, &content);
    let first_scan_time = start.elapsed();
    
    // Second scan should hit cache and be faster
    let start = std::time::Instant::now();
    let results2 = scanner.scan_buffer(buffer_id, version, &content);
    let second_scan_time = start.elapsed();
    
    // Results should be identical
    assert_eq!(results1.len(), results2.len());
    
    // Cache should have been used
    assert!(scanner.cache_stats().hits > 0, "Should have cache hits");
    assert!(scanner.cache_stats().hit_ratio() > 0.0, "Should have positive hit ratio");
    
    // Second scan should generally be faster (though this might be flaky on very fast systems)
    if first_scan_time.as_nanos() > 1000 {  // Only check if first scan took > 1μs
        assert!(second_scan_time <= first_scan_time, "Cached scan should not be slower");
    }
}

#[test]
fn test_large_file_handling() {
    // Generate a large file with many TODO items
    let mut large_content = String::new();
    for i in 0..1000 {
        large_content.push_str(&format!("// TODO: Task number {}\n", i));
        large_content.push_str(&format!("// Regular comment {}\n", i));
        if i % 10 == 0 {
            large_content.push_str(&format!("/* FIXME: Issue {}\n   multiline comment */\n", i));
        }
    }
    
    let start = std::time::Instant::now();
    let results = scan_file(&large_content, "rust");
    let scan_time = start.elapsed();
    
    // Should find approximately 1100 items (1000 TODOs + 100 FIXMEs)
    assert!(results.len() > 1000, "Should find many TODO items in large file");
    assert!(results.len() < 1200, "Should not have too many false positives");
    
    // Should complete in reasonable time (< 50ms for 1000+ TODOs)
    assert!(scan_time.as_millis() < 50, "Large file scan should complete quickly");
}

#[test]
fn test_empty_file() {
    let results = scan_file("", "rust");
    assert!(results.is_empty(), "Empty file should have no TODO items");
}

#[test]
fn test_file_with_no_todos() {
    let content = r#"
        fn main() {
            println!("Hello, world!");
        }
        
        // Regular comment
        /* Another comment */
    "#;
    
    let results = scan_file(content, "rust");
    assert!(results.is_empty(), "File without TODOs should return empty results");
}

#[test]
fn test_position_accuracy() {
    let content = "prefix // TODO: test message";
    let results = scan_file(content, "rust");
    
    assert_eq!(results.len(), 1);
    let todo = &results[0];
    
    // Check that positions are accurate
    assert_eq!(todo.start, 10); // Position of "TODO"
    assert!(todo.end > todo.start);
    assert!(todo.end <= content.len());
    
    // Extract the actual matched text
    let matched_text = &content[todo.start..todo.end];
    assert!(matched_text.starts_with("TODO"));
}

#[test]
fn test_multiple_todos_same_line() {
    let content = "// TODO: first item HACK: second item";
    let results = scan_file(content, "rust");
    
    assert_eq!(results.len(), 2, "Should find multiple TODOs on same line");
    
    // Should be sorted by position
    assert!(results[0].start < results[1].start);
    
    // Check keywords
    assert_eq!(results[0].keyword, "TODO");
    assert_eq!(results[1].keyword, "HACK");
}

#[test]
fn test_pattern_priorities() {
    let content = r#"
        // NOTE: low priority
        // TODO: medium priority  
        // SECURITY: high priority
        // BUG: high priority
    "#;
    
    let results = scan_file(content, "rust");
    assert_eq!(results.len(), 4);
    
    // Find priority values
    let note_priority = results.iter().find(|r| r.keyword == "NOTE").unwrap().priority;
    let todo_priority = results.iter().find(|r| r.keyword == "TODO").unwrap().priority;
    let security_priority = results.iter().find(|r| r.keyword == "SECURITY").unwrap().priority;
    let bug_priority = results.iter().find(|r| r.keyword == "BUG").unwrap().priority;
    
    // Check priority ordering (higher number = higher priority)
    assert!(security_priority > todo_priority, "SECURITY should have higher priority than TODO");
    assert!(bug_priority > todo_priority, "BUG should have higher priority than TODO");
    assert!(todo_priority > note_priority, "TODO should have higher priority than NOTE");
}