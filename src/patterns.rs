//! Pattern matching system for TODO/FIXME/HACK detection
//! 
//! This module provides configurable pattern matching with regex-based detection
//! of various TODO-style annotations in comments.

use regex::Regex;
use serde::{Deserialize, Serialize};

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct TodoPattern {
    pub keyword: String,
    pub regex: String,
    pub priority: u8,
    pub style: HighlightStyle,
    pub include_colon: bool,
    pub case_sensitive: bool,
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub enum HighlightStyle {
    Error,
    Warning,
    Info,
    Success,
    Custom {
        foreground: Option<String>,
        background: Option<String>,
        weight: Option<FontWeight>,
        underline: Option<UnderlineStyle>,
    },
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub enum FontWeight {
    Normal,
    Bold,
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub enum UnderlineStyle {
    None,
    Solid,
    Wavy,
    Dotted,
}

#[derive(Debug, PartialEq, Clone)]
pub struct TodoMatch {
    pub keyword: String,
    pub message: String,
    pub start: usize,
    pub end: usize,
    pub priority: u8,
    pub style: HighlightStyle,
}

pub struct PatternMatcher {
    patterns: Vec<CompiledPattern>,
}

struct CompiledPattern {
    pattern: TodoPattern,
    regex: Regex,
    quick_check: Option<String>, // For fast string contains check
}

impl PatternMatcher {
    pub fn new(patterns: Vec<TodoPattern>) -> Result<Self, regex::Error> {
        let mut compiled_patterns = Vec::new();
        
        for pattern in patterns {
            let regex = Regex::new(&pattern.regex)?;
            let quick_check = if pattern.case_sensitive {
                Some(pattern.keyword.clone())
            } else {
                Some(pattern.keyword.to_uppercase())
            };
            
            compiled_patterns.push(CompiledPattern {
                pattern,
                regex,
                quick_check,
            });
        }
        
        Ok(Self {
            patterns: compiled_patterns,
        })
    }
    
    pub fn find_all(&self, text: &str) -> Vec<TodoMatch> {
        let mut matches = Vec::new();
        
        for compiled in &self.patterns {
            // Quick check to avoid regex if keyword isn't present
            if let Some(ref quick_check) = compiled.quick_check {
                let search_text = if compiled.pattern.case_sensitive {
                    text
                } else {
                    // For case-insensitive, we need to search differently
                    // This is a simplified check - regex will do the real work
                    if !text.to_uppercase().contains(quick_check) {
                        continue;
                    }
                    text
                };
                
                if compiled.pattern.case_sensitive && !search_text.contains(quick_check) {
                    continue;
                }
            }
            
            // Find all matches with this pattern
            for cap in compiled.regex.captures_iter(text) {
                if let Some(m) = cap.get(0) {
                    let message = cap.get(2)
                        .map(|m| m.as_str().trim().to_string())
                        .unwrap_or_default();
                    
                    matches.push(TodoMatch {
                        keyword: compiled.pattern.keyword.clone(),
                        message,
                        start: m.start(),
                        end: m.end(),
                        priority: compiled.pattern.priority,
                        style: compiled.pattern.style.clone(),
                    });
                }
            }
        }
        
        // Sort by position in text
        matches.sort_by_key(|m| m.start);
        matches
    }
    
    pub fn default_patterns() -> Vec<TodoPattern> {
        vec![
            TodoPattern {
                keyword: "TODO".to_string(),
                regex: r"\b(TODO|todo|Todo)\b:?\s*(.*)".to_string(),
                priority: 1,
                style: HighlightStyle::Info,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "FIXME".to_string(),
                regex: r"\b(FIXME|fixme|FixMe)\b:?\s*(.*)".to_string(),
                priority: 2,
                style: HighlightStyle::Warning,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "HACK".to_string(),
                regex: r"\b(HACK|hack|Hack)\b:?\s*(.*)".to_string(),
                priority: 3,
                style: HighlightStyle::Error,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "NOTE".to_string(),
                regex: r"\b(NOTE|note|Note)\b:?\s*(.*)".to_string(),
                priority: 0,
                style: HighlightStyle::Success,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "BUG".to_string(),
                regex: r"\b(BUG|bug|Bug)\b:?\s*(.*)".to_string(),
                priority: 4,
                style: HighlightStyle::Error,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "OPTIMIZE".to_string(),
                regex: r"\b(OPTIMIZE|OPTIMI[SZ]E|optimi[sz]e)\b:?\s*(.*)".to_string(),
                priority: 1,
                style: HighlightStyle::Info,
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "DEPRECATED".to_string(),
                regex: r"\b(DEPRECATED|deprecated|Deprecated)\b:?\s*(.*)".to_string(),
                priority: 2,
                style: HighlightStyle::Custom {
                    foreground: Some("#7c7c7c".to_string()),
                    background: None,
                    weight: Some(FontWeight::Normal),
                    underline: Some(UnderlineStyle::Solid),
                },
                include_colon: true,
                case_sensitive: false,
            },
            TodoPattern {
                keyword: "SECURITY".to_string(),
                regex: r"\b(SECURITY|SEC|security|sec)\b:?\s*(.*)".to_string(),
                priority: 5,
                style: HighlightStyle::Custom {
                    foreground: Some("#ff0000".to_string()),
                    background: None,
                    weight: Some(FontWeight::Bold),
                    underline: Some(UnderlineStyle::Wavy),
                },
                include_colon: true,
                case_sensitive: false,
            },
        ]
    }
}

impl Default for PatternMatcher {
    fn default() -> Self {
        Self::new(Self::default_patterns()).expect("Default patterns should compile")
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use pretty_assertions::assert_eq;

    fn default_matcher() -> PatternMatcher {
        PatternMatcher::default()
    }

    #[test]
    fn test_basic_todo_detection() {
        let matcher = default_matcher();
        let text = "// TODO: Implement this function";
        
        let matches = matcher.find_all(text);
        assert_eq!(matches.len(), 1);
        assert_eq!(matches[0].keyword, "TODO");
        assert_eq!(matches[0].message, "Implement this function");
        assert_eq!(matches[0].start, 3);
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

    #[test]
    fn test_priority_ordering() {
        let matcher = default_matcher();
        let text = "// NOTE: low priority // SECURITY: high priority";
        
        let matches = matcher.find_all(text);
        assert_eq!(matches.len(), 2);
        // NOTE has priority 0, SECURITY has priority 5
        assert_eq!(matches[0].keyword, "NOTE");
        assert_eq!(matches[0].priority, 0);
        assert_eq!(matches[1].keyword, "SECURITY");
        assert_eq!(matches[1].priority, 5);
    }

    #[test]
    fn test_empty_message() {
        let matcher = default_matcher();
        let text = "// TODO:";
        
        let matches = matcher.find_all(text);
        assert_eq!(matches.len(), 1);
        assert_eq!(matches[0].keyword, "TODO");
        assert_eq!(matches[0].message, "");
    }

    #[test]
    fn test_no_colon() {
        let matcher = default_matcher();
        let text = "// TODO implement this";
        
        let matches = matcher.find_all(text);
        assert_eq!(matches.len(), 1);
        assert_eq!(matches[0].keyword, "TODO");
        assert_eq!(matches[0].message, "implement this");
    }
}