# Willow Testing Guide
## Comprehensive Testing Strategy for Zed Extensions

**Version:** 1.0.0  
**Author:** willibrandon  
**Date:** January 2025

## Testing Overview

Testing a Zed extension requires a multi-layered approach since we're dealing with WebAssembly, tree-sitter grammars, and editor integration. This guide uses standard Rust testing tools and focuses on practical, maintainable testing.

## Test Environment Setup

### 1. Prerequisites

```bash
# Standard Rust toolchain
rustup target add wasm32-wasip1

# Tree-sitter CLI for grammar testing
npm install -g tree-sitter-cli

# Benchmarking (using built-in cargo bench)
# No external tools needed

# Install Zed for manual testing
brew install --cask zed       # macOS
# or download from zed.dev for Linux/Windows
```

### 2. Project Test Structure

```
willow-zed/
├── src/
│   ├── lib.rs
│   ├── patterns.rs
│   └── cache.rs
├── tests/
│   ├── fixtures/
│   │   ├── sample_code/
│   │   │   ├── rust_todos.rs
│   │   │   ├── python_todos.py
│   │   │   ├── javascript_todos.js
│   │   │   └── mixed_todos.txt
│   │   └── edge_cases/
│   │       ├── nested_comments.rs
│   │       ├── unicode_todos.py
│   │       └── malformed_patterns.js
│   └── integration.rs
├── benches/
│   └── pattern_matching.rs
├── scripts/
│   ├── test.sh
│   ├── test_in_zed.sh
│   └── generate_fixtures.sh
└── Cargo.toml
```

## Unit Testing

### 1. Cargo.toml Test Configuration

```toml
[package]
name = "willow"
version = "0.1.0"
edition = "2021"

[lib]
crate-type = ["cdylib", "rlib"]  # rlib for testing

[dependencies]
zed_extension_api = "0.6.0"
serde = { version = "1.0", features = ["derive"] }
serde_json = "1.0"
regex = "1.10"

[dev-dependencies]
tempfile = "3.8"
pretty_assertions = "1.4"

[profile.test]
opt-level = 2  # Optimize tests for faster execution
```

### 2. Pattern Matching Tests

```rust
// src/patterns.rs (with inline tests)
use regex::Regex;
use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct TodoPattern {
    pub keyword: String,
    pub regex: Regex,
    pub priority: u8,
    pub style: String,
}

#[derive(Debug, PartialEq)]
pub struct TodoMatch {
    pub keyword: String,
    pub message: String,
    pub start: usize,
    pub end: usize,
}

pub struct PatternMatcher {
    patterns: Vec<TodoPattern>,
}

impl PatternMatcher {
    pub fn find_all(&self, text: &str) -> Vec<TodoMatch> {
        let mut matches = Vec::new();
        for pattern in &self.patterns {
            for cap in pattern.regex.captures_iter(text) {
                if let Some(m) = cap.get(0) {
                    matches.push(TodoMatch {
                        keyword: pattern.keyword.clone(),
                        message: cap.get(2)
                            .map(|m| m.as_str().trim().to_string())
                            .unwrap_or_default(),
                        start: m.start(),
                        end: m.end(),
                    });
                }
            }
        }
        matches.sort_by_key(|m| m.start);
        matches
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    fn default_matcher() -> PatternMatcher {
        PatternMatcher {
            patterns: vec![
                TodoPattern {
                    keyword: "TODO".to_string(),
                    regex: Regex::new(r"\b(TODO|todo|Todo)\b:?\s*(.*)").unwrap(),
                    priority: 1,
                    style: "info".to_string(),
                },
                TodoPattern {
                    keyword: "FIXME".to_string(),
                    regex: Regex::new(r"\b(FIXME|fixme|FixMe)\b:?\s*(.*)").unwrap(),
                    priority: 2,
                    style: "warning".to_string(),
                },
                TodoPattern {
                    keyword: "HACK".to_string(),
                    regex: Regex::new(r"\b(HACK|hack|Hack)\b:?\s*(.*)").unwrap(),
                    priority: 3,
                    style: "error".to_string(),
                },
            ],
        }
    }

    #[test]
    fn test_basic_todo_detection() {
        let matcher = default_matcher();
        let text = "// TODO: Implement this function";
        
        let matches = matcher.find_all(text);
        assert_eq!(matches.len(), 1);
        assert_eq!(matches[0].keyword, "TODO");
        assert_eq!(matches[0].message, "Implement this function");
    }

    #[test]
    fn test_multiple_patterns_same_line() {
        let matcher = default_matcher();
        let text = "// TODO: Fix this HACK: Temporary workaround";
        
        let matches = matcher.find_all(text);
        assert_eq!(matches.len(), 2);
        assert_eq!(matches[0].keyword, "TODO");
        assert_eq!(matches[1].keyword, "HACK");
    }

    #[test]
    fn test_case_insensitive_matching() {
        let matcher = default_matcher();
        let test_cases = [
            ("// TODO: uppercase", "TODO"),
            ("// todo: lowercase", "TODO"),
            ("// Todo: titlecase", "TODO"),
            ("// FIXME: test", "FIXME"),
            ("// fixme: test", "FIXME"),
        ];
        
        for (text, expected_keyword) in test_cases {
            let matches = matcher.find_all(text);
            assert_eq!(matches.len(), 1, "Failed for: {}", text);
            assert_eq!(matches[0].keyword, expected_keyword);
        }
    }

    #[test]
    fn test_unicode_support() {
        let matcher = default_matcher();
        let test_cases = [
            "// TODO: 修复这个问题 🔧",
            "// FIXME: Ñoño está roto",
            "// HACK: Временное решение",
            "// TODO: 日本語のコメント",
        ];
        
        for text in test_cases {
            let matches = matcher.find_all(text);
            assert_eq!(matches.len(), 1, "Failed for: {}", text);
            assert!(!matches[0].message.is_empty());
        }
    }

    #[test]
    fn test_word_boundaries() {
        let matcher = default_matcher();
        let test_cases = [
            ("// TODO: valid", true),
            ("// TODOLIST: invalid", false),
            ("// MY_TODO: invalid", false),
            ("// TODO_ITEM: invalid", false),
            ("// aTODOb: invalid", false),
        ];
        
        for (text, should_match) in test_cases {
            let matches = matcher.find_all(text);
            assert_eq!(!matches.is_empty(), should_match, "Failed for: {}", text);
        }
    }

    #[test]
    fn test_multiline_comments() {
        let matcher = default_matcher();
        let text = r#"
/*
 * TODO: First item
 * FIXME: Second item
 * Regular comment
 * HACK: Third item
 */
"#;
        
        let matches = matcher.find_all(text);
        assert_eq!(matches.len(), 3);
        assert_eq!(matches[0].keyword, "TODO");
        assert_eq!(matches[1].keyword, "FIXME");
        assert_eq!(matches[2].keyword, "HACK");
    }

    #[test]
    fn test_position_tracking() {
        let matcher = default_matcher();
        let text = "prefix // TODO: test";
        
        let matches = matcher.find_all(text);
        assert_eq!(matches.len(), 1);
        assert_eq!(matches[0].start, 10); // Position of "TODO"
        assert!(matches[0].end > matches[0].start);
    }
}
```

### 3. Cache Tests

```rust
// src/cache.rs (with inline tests)
use std::collections::HashMap;

#[derive(Debug, Clone, Copy, Hash, Eq, PartialEq)]
pub struct BufferId(pub u64);

#[derive(Debug)]
pub struct ResultCache {
    entries: HashMap<(BufferId, u64), Vec<TodoMatch>>,
    max_size: usize,
    hits: usize,
    misses: usize,
}

impl ResultCache {
    pub fn new(max_size: usize) -> Self {
        Self {
            entries: HashMap::new(),
            max_size,
            hits: 0,
            misses: 0,
        }
    }

    pub fn get(&mut self, buffer_id: BufferId, version: u64) -> Option<&Vec<TodoMatch>> {
        let result = self.entries.get(&(buffer_id, version));
        if result.is_some() {
            self.hits += 1;
        } else {
            self.misses += 1;
        }
        result
    }

    pub fn insert(&mut self, buffer_id: BufferId, version: u64, items: Vec<TodoMatch>) {
        if self.entries.len() >= self.max_size {
            // Simple eviction: remove first item (not true LRU, but simple)
            if let Some(key) = self.entries.keys().next().cloned() {
                self.entries.remove(&key);
            }
        }
        self.entries.insert((buffer_id, version), items);
    }

    pub fn hit_ratio(&self) -> f64 {
        let total = self.hits + self.misses;
        if total == 0 {
            0.0
        } else {
            self.hits as f64 / total as f64
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::patterns::TodoMatch;

    #[test]
    fn test_cache_basic_operations() {
        let mut cache = ResultCache::new(10);
        let buffer_id = BufferId(1);
        let items = vec![
            TodoMatch {
                keyword: "TODO".to_string(),
                message: "Test".to_string(),
                start: 0,
                end: 10,
            }
        ];
        
        cache.insert(buffer_id, 1, items.clone());
        
        // Hit
        assert!(cache.get(buffer_id, 1).is_some());
        assert_eq!(cache.hits, 1);
        
        // Miss (different version)
        assert!(cache.get(buffer_id, 2).is_none());
        assert_eq!(cache.misses, 1);
        
        // Hit ratio
        assert_eq!(cache.hit_ratio(), 0.5);
    }

    #[test]
    fn test_cache_eviction() {
        let mut cache = ResultCache::new(2);
        
        cache.insert(BufferId(1), 1, vec![]);
        cache.insert(BufferId(2), 1, vec![]);
        cache.insert(BufferId(3), 1, vec![]); // Should trigger eviction
        
        // Can't guarantee which one was evicted in HashMap, 
        // but we should have exactly 2 entries
        assert_eq!(cache.entries.len(), 2);
    }

    #[test]
    fn test_cache_version_invalidation() {
        let mut cache = ResultCache::new(10);
        let buffer_id = BufferId(1);
        
        cache.insert(buffer_id, 1, vec![]);
        assert!(cache.get(buffer_id, 1).is_some());
        
        // Different version should miss
        assert!(cache.get(buffer_id, 2).is_none());
    }
}
```

## Integration Tests

### 1. Full Integration Test

```rust
// tests/integration.rs
use std::fs;
use std::path::Path;
use willow::{WillowExtension, scan_file};

fn load_fixture(name: &str) -> String {
    let path = Path::new("tests/fixtures/sample_code").join(name);
    fs::read_to_string(path).expect("Failed to load fixture")
}

#[test]
fn test_rust_file_scanning() {
    let content = load_fixture("rust_todos.rs");
    let results = scan_file(&content, "rust");
    
    // Verify we found all expected TODOs
    assert!(results.iter().any(|r| r.keyword == "TODO"));
    assert!(results.iter().any(|r| r.keyword == "FIXME"));
    assert!(results.iter().any(|r| r.keyword == "HACK"));
}

#[test]
fn test_python_file_scanning() {
    let content = load_fixture("python_todos.py");
    let results = scan_file(&content, "python");
    
    assert!(!results.is_empty());
    // Python specific: should handle # comments
    assert!(results.iter().any(|r| r.message.contains("Python")));
}

#[test]
fn test_javascript_file_scanning() {
    let content = load_fixture("javascript_todos.js");
    let results = scan_file(&content, "javascript");
    
    assert!(!results.is_empty());
    // Should handle both // and /* */ comments
}

#[test]
fn test_edge_case_nested_comments() {
    let content = load_fixture("../edge_cases/nested_comments.rs");
    let results = scan_file(&content, "rust");
    
    // Should handle nested comment structures correctly
    for result in &results {
        assert!(!result.message.contains("*/"));
        assert!(!result.message.contains("//"));
    }
}

#[test]
fn test_unicode_edge_cases() {
    let content = load_fixture("../edge_cases/unicode_todos.py");
    let results = scan_file(&content, "python");
    
    // Should properly handle various unicode scenarios
    assert!(!results.is_empty());
}
```

### 2. Test Fixtures

```rust
// tests/fixtures/sample_code/rust_todos.rs
// TODO: Implement the main function
fn main() {
    // FIXME: This is broken
    let x = 42;
    
    /* HACK: Temporary workaround
     * until we fix the underlying issue
     */
    println!("Hello");
    
    // NOTE: This is important
    // BUG: Off by one error here
    // OPTIMIZE: Could be faster
    // DEPRECATED: Use new_function instead
    // SECURITY: Validate input
}

// Regular comment without keywords
// This TODO: is in the middle of text
// todolist: should not match (no word boundary)
```

```python
# tests/fixtures/sample_code/python_todos.py
# TODO: Add error handling
def process_data(data):
    # FIXME: Handle None values
    if data is None:
        return
    
    # HACK: Quick fix for Python 3.9
    result = str(data)
    
    """
    TODO: Add documentation
    FIXME: Update for new API
    """
    
    # NOTE: 中文注释 TODO: 支持Unicode
    return result
```

```javascript
// tests/fixtures/sample_code/javascript_todos.js
// TODO: Convert to TypeScript
function processData(data) {
    // FIXME: Add type checking
    if (!data) return null;
    
    /* TODO: Refactor this mess
     * HACK: Works for now
     * NOTE: Performance critical
     */
    
    // BUG: Doesn't handle arrays
    return data.toString();
}

/* Regular block comment */
// todoapp: should not match
```

## Performance Testing

### 1. Benchmark Tests

```rust
// benches/pattern_matching.rs
use criterion::{black_box, criterion_group, criterion_main, Criterion};
use willow::PatternMatcher;

fn generate_text(size: usize) -> String {
    let mut text = String::new();
    for i in 0..size {
        if i % 10 == 0 {
            text.push_str(&format!("// TODO: Task number {}\n", i));
        } else if i % 15 == 0 {
            text.push_str(&format!("// FIXME: Issue {}\n", i));
        } else {
            text.push_str(&format!("// Regular comment {}\n", i));
        }
    }
    text
}

fn bench_small_file(c: &mut Criterion) {
    let matcher = PatternMatcher::default();
    let text = generate_text(100);
    
    c.bench_function("small_file_100_lines", |b| {
        b.iter(|| {
            matcher.find_all(black_box(&text))
        });
    });
}

fn bench_medium_file(c: &mut Criterion) {
    let matcher = PatternMatcher::default();
    let text = generate_text(1000);
    
    c.bench_function("medium_file_1k_lines", |b| {
        b.iter(|| {
            matcher.find_all(black_box(&text))
        });
    });
}

fn bench_large_file(c: &mut Criterion) {
    let matcher = PatternMatcher::default();
    let text = generate_text(10000);
    
    c.bench_function("large_file_10k_lines", |b| {
        b.iter(|| {
            matcher.find_all(black_box(&text))
        });
    });
}

fn bench_cache_operations(c: &mut Criterion) {
    use willow::{ResultCache, BufferId};
    
    c.bench_function("cache_insert_and_get", |b| {
        let mut cache = ResultCache::new(1000);
        let buffer_id = BufferId(1);
        let items = vec![];
        
        b.iter(|| {
            cache.insert(buffer_id, 1, items.clone());
            cache.get(buffer_id, 1);
        });
    });
}

criterion_group!(benches, 
    bench_small_file, 
    bench_medium_file, 
    bench_large_file,
    bench_cache_operations
);
criterion_main!(benches);
```

### 2. Add to Cargo.toml

```toml
[[bench]]
name = "pattern_matching"
harness = false

[dev-dependencies]
criterion = "0.5"
```

## Manual Testing in Zed

### 1. Test Script

```bash
#!/bin/bash
# scripts/test_in_zed.sh

set -e

echo "Building Willow extension..."
cargo build --release --target wasm32-wasip1

echo "Installing in Zed..."
# Kill any running Zed instances
pkill -f "Zed" || true

# Start Zed in foreground for debugging
echo "Starting Zed with debug output..."
zed --foreground &
ZED_PID=$!

sleep 3

echo "Extension installed. Testing with sample files..."
echo "Check the following:"
echo "1. TODO highlighting in comments"
echo "2. FIXME highlighting in different color"
echo "3. HACK highlighting as error/warning"
echo "4. Performance with large files"

# Open test files
zed tests/fixtures/sample_code/*.rs tests/fixtures/sample_code/*.py tests/fixtures/sample_code/*.js

echo "Press Enter to stop Zed and see logs..."
read

kill $ZED_PID
```

### 2. Visual Testing Checklist

```markdown
# Manual Testing Checklist

## Basic Functionality
- [ ] TODO patterns are highlighted
- [ ] FIXME patterns are highlighted in different color
- [ ] HACK patterns show as warnings/errors
- [ ] NOTE patterns are visible
- [ ] BUG patterns stand out

## Language Support
- [ ] Rust (.rs files)
- [ ] Python (.py files)
- [ ] JavaScript (.js files)
- [ ] TypeScript (.ts files)
- [ ] Go (.go files)
- [ ] HTML (.html files)
- [ ] CSS (.css files)
- [ ] Shell scripts (.sh files)

## Edge Cases
- [ ] Unicode characters in comments
- [ ] Multi-line block comments
- [ ] Nested comments
- [ ] Mixed case (TODO, todo, Todo)
- [ ] No false positives (TODOLIST, MY_TODO)

## Performance
- [ ] Instant highlighting on file open
- [ ] No lag when typing
- [ ] Handles 10K+ line files
- [ ] Memory usage stays reasonable

## Theme Integration
- [ ] Works with light themes
- [ ] Works with dark themes
- [ ] Colors are distinguishable
- [ ] Respects user theme preferences
```

## Tree-sitter Grammar Testing

### 1. Grammar Test Script

```bash
#!/bin/bash
# scripts/test_grammar.sh

cd tree-sitter-todo-injections

# Generate parser
tree-sitter generate

# Run tests
tree-sitter test

# Test specific patterns
echo "Testing TODO patterns..."
echo "TODO: test" | tree-sitter parse -

echo "Testing FIXME patterns..."
echo "FIXME: test" | tree-sitter parse -

echo "Testing edge cases..."
echo "TODOLIST: should not match" | tree-sitter parse -
```

### 2. Grammar Test Cases

```
# tree-sitter-todo-injections/test/corpus/basic.txt
================
TODO Detection
================

TODO: Basic test

---

(source_file
  (todo_item
    (message)))

================
Multiple Keywords
================

TODO: First
FIXME: Second
HACK: Third

---

(source_file
  (todo_item
    (message))
  (fixme_item
    (message))
  (hack_item
    (message)))

================
Case Variations
================

todo: lowercase
TODO: uppercase
Todo: titlecase

---

(source_file
  (todo_item
    (message))
  (todo_item
    (message))
  (todo_item
    (message)))
```

## Continuous Integration

### 1. GitHub Actions Workflow

```yaml
# .github/workflows/test.yml
name: Test

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  test:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Install Rust
      uses: actions-rs/toolchain@v1
      with:
        toolchain: stable
        target: wasm32-wasip1
        override: true
    
    - name: Run tests
      run: cargo test --all-features
    
    - name: Run benchmarks
      run: cargo bench --no-run
    
    - name: Build WASM
      run: cargo build --release --target wasm32-wasip1
    
    - name: Check WASM size
      run: |
        SIZE=$(stat -f%z target/wasm32-wasip1/release/willow.wasm 2>/dev/null || stat -c%s target/wasm32-wasip1/release/willow.wasm)
        echo "WASM size: $SIZE bytes"
        if [ $SIZE -gt 1048576 ]; then
          echo "Warning: WASM size exceeds 1MB"
          exit 1
        fi
```

## Test Execution

```bash
# Run all tests
cargo test

# Run specific test
cargo test test_basic_todo_detection

# Run with output
cargo test -- --nocapture

# Run benchmarks
cargo bench

# Generate coverage report (requires llvm-tools)
cargo test
cargo profdata -- merge -sparse default_*.profraw -o default.profdata
cargo cov -- report --instr-profile=default.profdata
```

## Performance Targets

| Test | Target | Measurement |
|------|--------|-------------|
| Small file (100 lines) | <1ms | cargo bench |
| Medium file (1K lines) | <5ms | cargo bench |
| Large file (10K lines) | <50ms | cargo bench |
| Cache hit | <100ns | cargo bench |
| WASM size | <1MB | Build output |
| Memory per buffer | <100KB | Manual testing |

---

*This testing guide provides comprehensive coverage without unnecessary dependencies, focusing on Rust's built-in testing capabilities and practical validation in Zed.*