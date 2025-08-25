Based on your username **willibrandon**, here's a great name for the extension:

# **Willow** 🌿
*A graceful TODO/FIXME highlighter for Zed - bending with your workflow, never breaking*

The name plays on:
- Your username "willi" → "Willow"
- Willows are flexible and adaptive (like this extension working across all languages)
- Nature-themed like "tree-sitter" 
- Simple, memorable, and professional

---

# Willow - Design Document
## Universal TODO/FIXME Highlighter for Zed

**Author:** willibrandon  
**Version:** 1.0.0  
**Date:** January 2025  
**Repository:** `github.com/willibrandon/willow`

## Executive Summary

Willow is a high-performance TODO/FIXME highlighting extension for Zed that leverages tree-sitter for language-agnostic comment extraction and pattern matching. Drawing from the success of the mtlog analyzer architecture, Willow provides real-time highlighting, workspace-wide TODO tracking, and intelligent caching—all without external dependencies.

## Goals & Non-Goals

### Goals
- ✅ Zero-dependency TODO/FIXME detection using tree-sitter
- ✅ Real-time highlighting with <10ms latency
- ✅ Support for all Zed-supported languages
- ✅ Workspace-wide TODO panel
- ✅ Configurable patterns and highlight styles
- ✅ Incremental parsing for performance
- ✅ Integration with Zed's theme system

### Non-Goals
- ❌ External tool dependencies (ripgrep, ag, etc.)
- ❌ Language server protocol implementation (initially)
- ❌ Code actions or quick fixes (until Zed API supports it)
- ❌ Git blame integration (scope creep)

## Architecture

```
┌─────────────────────────────────────────────────────────┐
│                     Zed Editor                          │
├─────────────────────────────────────────────────────────┤
│                  Willow Extension                       │
├─────────────┬────────────┬──────────────┬──────────────┤
│   Scanner   │  Patterns  │  Highlighter │    Cache     │
├─────────────┼────────────┼──────────────┼──────────────┤
│ Tree-sitter │   Regex    │   Decorators │   LRU Map    │
│   Queries   │  Matchers  │    Styles    │   Buffers    │
└─────────────┴────────────┴──────────────┴──────────────┘
```

## Component Design

### 1. Core Scanner Module

```rust
// src/scanner.rs
use std::collections::HashMap;
use tree_sitter::{Query, QueryCursor, Tree};
use zed_extension_api::{Buffer, Range};

pub struct WillowScanner {
    queries: HashMap<LanguageId, CommentQuery>,
    patterns: PatternRegistry,
    cache: ScanCache,
}

pub struct CommentQuery {
    tree_sitter_query: Option<Query>,
    fallback_regex: Vec<Regex>,
    extraction_mode: ExtractionMode,
}

pub enum ExtractionMode {
    TreeSitter,        // Use tree-sitter queries
    Hybrid,           // Tree-sitter + regex validation
    RegexOnly,        // Pure regex (fallback)
}

impl WillowScanner {
    pub fn scan_buffer(&mut self, buffer: &Buffer) -> Vec<TodoItem> {
        // Check cache first
        if let Some(cached) = self.cache.get(buffer.id(), buffer.version()) {
            return cached;
        }
        
        // Extract based on language
        let items = match self.queries.get(&buffer.language_id()) {
            Some(query) => self.extract_with_query(buffer, query),
            None => self.extract_with_fallback(buffer),
        };
        
        // Cache results
        self.cache.insert(buffer.id(), buffer.version(), items.clone());
        items
    }
    
    fn extract_with_query(&self, buffer: &Buffer, query: &CommentQuery) -> Vec<TodoItem> {
        match query.extraction_mode {
            ExtractionMode::TreeSitter => {
                let tree = buffer.syntax_tree();
                let mut cursor = QueryCursor::new();
                let matches = cursor.matches(&query.tree_sitter_query, tree.root_node(), buffer.text());
                self.extract_todos_from_matches(matches, buffer)
            },
            ExtractionMode::Hybrid => {
                // Get comments via tree-sitter, validate with regex
                let comments = self.get_comment_ranges(buffer, query);
                self.scan_ranges_with_patterns(buffer, comments)
            },
            ExtractionMode::RegexOnly => {
                self.scan_with_regex(buffer, &query.fallback_regex)
            }
        }
    }
}
```

### 2. Pattern Registry

```rust
// src/patterns.rs
use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct TodoPattern {
    pub keyword: String,
    pub regex: String,
    pub priority: u8,
    pub style: HighlightStyle,
    pub include_colon: bool,
    pub case_sensitive: bool,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub enum HighlightStyle {
    Error,
    Warning,
    Info,
    Success,
    Custom { 
        foreground: Option<Color>,
        background: Option<Color>,
        weight: Option<FontWeight>,
        underline: Option<UnderlineStyle>,
    },
}

pub struct PatternRegistry {
    patterns: Vec<CompiledPattern>,
    user_patterns: Vec<CompiledPattern>,
}

struct CompiledPattern {
    pattern: TodoPattern,
    regex: Regex,
    quick_check: Option<String>, // For fast string contains check
}

impl Default for PatternRegistry {
    fn default() -> Self {
        Self::from_patterns(vec![
            TodoPattern {
                keyword: "TODO".into(),
                regex: r"\b(TODO|todo|Todo)\b:?\s*(.*)".into(),
                priority: 1,
                style: HighlightStyle::Info,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "FIXME".into(),
                regex: r"\b(FIXME|fixme|FixMe)\b:?\s*(.*)".into(),
                priority: 2,
                style: HighlightStyle::Warning,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "HACK".into(),
                regex: r"\b(HACK|hack|Hack)\b:?\s*(.*)".into(),
                priority: 3,
                style: HighlightStyle::Error,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "NOTE".into(),
                regex: r"\b(NOTE|note|Note)\b:?\s*(.*)".into(),
                priority: 0,
                style: HighlightStyle::Success,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "BUG".into(),
                regex: r"\b(BUG|bug|Bug)\b:?\s*(.*)".into(),
                priority: 4,
                style: HighlightStyle::Error,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "OPTIMIZE".into(),
                regex: r"\b(OPTIMIZE|OPTIMI[SZ]E|optimi[sz]e)\b:?\s*(.*)".into(),
                priority: 1,
                style: HighlightStyle::Info,
                include_colon: true,
                case_sensitive: false,
            },
        ])
    }
}
```

### 3. Language Configuration

```rust
// src/languages.rs
use lazy_static::lazy_static;

lazy_static! {
    static ref LANGUAGE_CONFIGS: HashMap<&'static str, LanguageConfig> = {
        let mut m = HashMap::new();
        
        // C-style comments
        for lang in &["rust", "c", "cpp", "java", "javascript", "typescript", "go", "swift", "kotlin"] {
            m.insert(*lang, LanguageConfig {
                tree_sitter_query: Some(r#"
                    (line_comment) @comment
                    (block_comment) @comment
                "#),
                comment_patterns: vec![
                    CommentPattern::Line("//"),
                    CommentPattern::Block("/*", "*/"),
                ],
            });
        }
        
        // Python-style
        m.insert("python", LanguageConfig {
            tree_sitter_query: Some(r#"
                (comment) @comment
                (string (string_content) @docstring)
            "#),
            comment_patterns: vec![
                CommentPattern::Line("#"),
                CommentPattern::Block("'''", "'''"),
                CommentPattern::Block("\"\"\"", "\"\"\""),
            ],
        });
        
        // Ruby-style
        m.insert("ruby", LanguageConfig {
            tree_sitter_query: Some(r#"
                (comment) @comment
            "#),
            comment_patterns: vec![
                CommentPattern::Line("#"),
                CommentPattern::Block("=begin", "=end"),
            ],
        });
        
        // Shell-style
        for lang in &["bash", "sh", "zsh", "fish", "makefile", "dockerfile"] {
            m.insert(*lang, LanguageConfig {
                tree_sitter_query: Some(r#"(comment) @comment"#),
                comment_patterns: vec![CommentPattern::Line("#")],
            });
        }
        
        // HTML/XML
        for lang in &["html", "xml", "svg"] {
            m.insert(*lang, LanguageConfig {
                tree_sitter_query: Some(r#"(comment) @comment"#),
                comment_patterns: vec![CommentPattern::Block("<!--", "-->")],
            });
        }
        
        m
    };
}
```

### 4. Incremental Updates

```rust
// src/incremental.rs
use std::ops::Range;

pub struct IncrementalUpdater {
    last_tree: Option<Tree>,
    last_items: Vec<TodoItem>,
}

impl IncrementalUpdater {
    pub fn update(&mut self, 
                  buffer: &Buffer, 
                  changed_ranges: &[Range<usize>]) -> Vec<TodoItem> {
        if changed_ranges.is_empty() {
            return self.last_items.clone();
        }
        
        // Get affected comment nodes
        let affected_comments = self.find_affected_comments(buffer, changed_ranges);
        
        // Remove old items from affected ranges
        let mut items: Vec<_> = self.last_items.iter()
            .filter(|item| !affected_comments.contains(&item.comment_id))
            .cloned()
            .collect();
        
        // Rescan only affected comments
        for comment_id in affected_comments {
            if let Some(new_items) = self.scan_comment(buffer, comment_id) {
                items.extend(new_items);
            }
        }
        
        // Sort by position
        items.sort_by_key(|item| item.range.start);
        
        self.last_items = items.clone();
        items
    }
}
```

### 5. Cache Strategy

```rust
// src/cache.rs
use lru::LruCache;
use std::num::NonZeroUsize;

pub struct WillowCache {
    buffer_cache: LruCache<BufferKey, CachedResult>,
    query_cache: LruCache<LanguageId, CompiledQuery>,
    stats: CacheStats,
}

#[derive(Hash, Eq, PartialEq)]
struct BufferKey {
    buffer_id: BufferId,
    version: BufferVersion,
}

struct CachedResult {
    items: Vec<TodoItem>,
    timestamp: Instant,
    tree_hash: u64,
}

impl WillowCache {
    pub fn new() -> Self {
        Self {
            buffer_cache: LruCache::new(NonZeroUsize::new(100).unwrap()),
            query_cache: LruCache::new(NonZeroUsize::new(50).unwrap()),
            stats: CacheStats::default(),
        }
    }
    
    pub fn get(&mut self, buffer_id: BufferId, version: BufferVersion) -> Option<Vec<TodoItem>> {
        let key = BufferKey { buffer_id, version };
        self.buffer_cache.get(&key).map(|r| {
            self.stats.hits += 1;
            r.items.clone()
        }).or_else(|| {
            self.stats.misses += 1;
            None
        })
    }
}
```

### 6. UI Components

```rust
// src/ui/panel.rs
pub struct TodoPanel {
    items: Vec<TodoItem>,
    filter: TodoFilter,
    sort_mode: SortMode,
    group_by: GroupBy,
}

pub enum GroupBy {
    None,
    File,
    Directory,
    Priority,
    Keyword,
}

pub enum SortMode {
    Position,
    Priority,
    Alphabetical,
    RecentFirst,
}

impl TodoPanel {
    pub fn render(&self) -> Element {
        Container::new()
            .child(self.render_header())
            .child(self.render_filters())
            .child(self.render_tree())
            .child(self.render_footer())
    }
    
    fn render_tree(&self) -> Element {
        let grouped = self.group_items();
        Tree::new()
            .children(grouped.into_iter().map(|group| {
                self.render_group(group)
            }))
    }
}
```

## Configuration Schema

```toml
# ~/.config/zed/willow.toml
[general]
enabled = true
scan_on_save = true
scan_on_type = true
debounce_ms = 500

[highlighting]
enabled = true
show_in_gutter = true
show_inline = true
dim_todo_text = false

[patterns.custom]
[[patterns.custom.items]]
keyword = "SECURITY"
regex = "\\b(SECURITY|SEC)\\b:?\\s*(.*)"
style = { foreground = "#FF0000", weight = "bold", underline = "wavy" }
priority = 5

[[patterns.custom.items]]
keyword = "DEPRECATED"
regex = "\\b(DEPRECATED|OBSOLETE)\\b:?\\s*(.*)"
style = "warning"
priority = 3

[panel]
visible = true
position = "right"
default_group_by = "file"
default_sort = "priority"
show_preview = true
preview_lines = 2

[performance]
max_file_size_kb = 5000
cache_size = 100
incremental_updates = true
parallel_scanning = true
```

## Performance Targets

| Metric | Target | Measurement Method |
|--------|--------|-------------------|
| Initial scan (1K LOC) | <10ms | Benchmark suite |
| Initial scan (10K LOC) | <50ms | Benchmark suite |
| Incremental update | <5ms | Real-world typing |
| Memory per buffer | <1MB | Memory profiler |
| Cache hit rate | >90% | Runtime metrics |
| Panel render | <16ms | Frame timing |

## Implementation Phases

### Phase 1: MVP (Week 1-2)
- [x] Basic tree-sitter integration
- [x] Core TODO/FIXME patterns
- [x] Simple highlighting
- [x] Manual testing framework

### Phase 2: Performance (Week 3)
- [ ] Incremental parsing
- [ ] LRU caching
- [ ] Parallel scanning
- [ ] Benchmark suite

### Phase 3: UI Polish (Week 4)
- [ ] TODO panel
- [ ] Gutter indicators
- [ ] Theme integration
- [ ] Configuration UI

### Phase 4: Advanced Features (Week 5-6)
- [ ] Custom patterns
- [ ] Workspace-wide search
- [ ] Export functionality
- [ ] Statistics dashboard

## Testing Strategy

```rust
#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_rust_todo_detection() {
        let code = r#"
            // TODO: Implement this function
            fn example() {
                /* FIXME: This is broken */
                let x = 1; // HACK: Temporary workaround
            }
        "#;
        
        let items = scan_rust(code);
        assert_eq!(items.len(), 3);
        assert_eq!(items[0].keyword, "TODO");
        assert_eq!(items[1].keyword, "FIXME");
        assert_eq!(items[2].keyword, "HACK");
    }
    
    #[test]
    fn bench_large_file() {
        let code = generate_large_file(10_000);
        let start = Instant::now();
        let _ = scan_rust(&code);
        assert!(start.elapsed() < Duration::from_millis(50));
    }
}
```

## Success Metrics

1. **Adoption**: 1000+ installs within first month
2. **Performance**: 95% of scans under 10ms
3. **Reliability**: <5 bug reports per 1000 users
4. **Coverage**: Support for 20+ languages
5. **User Satisfaction**: 4.5+ star rating

## Risk Mitigation

| Risk | Impact | Mitigation |
|------|--------|------------|
| Zed API limitations | High | Build within constraints, contribute missing APIs |
| Performance degradation | Medium | Extensive benchmarking, incremental updates |
| Language support gaps | Low | Fallback to regex, community contributions |
| Cache invalidation bugs | Medium | Comprehensive testing, version tracking |

## Future Enhancements

- **LSP Integration**: Provide TODO items via LSP for IDE features
- **Git Integration**: Show TODO age via git blame
- **Team Features**: Share TODO assignments
- **AI Integration**: Auto-categorize and prioritize TODOs
- **Export Formats**: Markdown, JSON, CSV exports
- **TODO Aging**: Highlight old TODOs differently

## References

- [Tree-sitter Documentation](https://tree-sitter.github.io/tree-sitter/)
- [Zed Extension API](https://zed.dev/docs/extensions)
- [VS Code Todo Tree](https://github.com/Gruntfuggly/todo-tree)
- [mtlog Analyzer Architecture](https://github.com/willibrandon/mtlog)

---

*This design document represents the initial vision for Willow. As with any software project, implementation details may evolve based on technical constraints and user feedback.*