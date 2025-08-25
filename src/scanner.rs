//! Scanner module for extracting TODOs from source code
//! 
//! This module provides the main scanning functionality that combines
//! pattern matching with caching for high performance.

use crate::patterns::{PatternMatcher, TodoPattern, TodoMatch};
use crate::cache::{ResultCache, BufferId, BufferVersion};

pub struct WillowScanner {
    matcher: PatternMatcher,
    cache: ResultCache,
}

impl WillowScanner {
    pub fn new(patterns: Vec<TodoPattern>) -> Self {
        let matcher = PatternMatcher::new(patterns)
            .expect("Failed to compile TODO patterns");
        let cache = ResultCache::default();
        
        Self {
            matcher,
            cache,
        }
    }

    pub fn scan_buffer(&mut self, buffer_id: BufferId, version: BufferVersion, text: &str) -> Vec<TodoMatch> {
        // Check cache first
        if let Some(cached) = self.cache.get(buffer_id, version) {
            return cached;
        }
        
        // Scan the text
        let matches = self.matcher.find_all(text);
        
        // Cache the results
        self.cache.insert(buffer_id, version, matches.clone());
        
        matches
    }

    pub fn invalidate_buffer(&mut self, buffer_id: BufferId) {
        self.cache.invalidate_buffer(buffer_id);
    }

    pub fn cache_stats(&self) -> &crate::cache::CacheStats {
        self.cache.stats()
    }

    pub fn clear_cache(&mut self) {
        self.cache.clear();
    }
}

impl Default for WillowScanner {
    fn default() -> Self {
        Self::new(PatternMatcher::default_patterns())
    }
}

// Convenience function for scanning files without managing scanner state
pub fn scan_file(text: &str, _language: &str) -> Vec<TodoMatch> {
    let matcher = PatternMatcher::default();
    matcher.find_all(text)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_scanner_basic_functionality() {
        let mut scanner = WillowScanner::default();
        let buffer_id = BufferId::new(1);
        let version = BufferVersion::new(1);
        let text = "// TODO: Implement this\n// FIXME: Fix this issue";
        
        let matches = scanner.scan_buffer(buffer_id, version, text);
        assert_eq!(matches.len(), 2);
        assert_eq!(matches[0].keyword, "TODO");
        assert_eq!(matches[1].keyword, "FIXME");
    }

    #[test]
    fn test_scanner_caching() {
        let mut scanner = WillowScanner::default();
        let buffer_id = BufferId::new(1);
        let version = BufferVersion::new(1);
        let text = "// TODO: Test caching";
        
        // First scan should miss cache
        let matches1 = scanner.scan_buffer(buffer_id, version, text);
        assert_eq!(scanner.cache_stats().misses, 1);
        assert_eq!(scanner.cache_stats().hits, 0);
        
        // Second scan with same version should hit cache
        let matches2 = scanner.scan_buffer(buffer_id, version, text);
        assert_eq!(scanner.cache_stats().hits, 1);
        assert_eq!(matches1.len(), matches2.len());
    }

    #[test]
    fn test_scanner_version_invalidation() {
        let mut scanner = WillowScanner::default();
        let buffer_id = BufferId::new(1);
        let version1 = BufferVersion::new(1);
        let version2 = BufferVersion::new(2);
        let text = "// TODO: Test version";
        
        // Scan with version 1
        scanner.scan_buffer(buffer_id, version1, text);
        assert_eq!(scanner.cache_stats().misses, 1);
        
        // Scan with version 2 should miss cache
        scanner.scan_buffer(buffer_id, version2, text);
        assert_eq!(scanner.cache_stats().misses, 2);
    }

    #[test]
    fn test_scanner_buffer_invalidation() {
        let mut scanner = WillowScanner::default();
        let buffer_id = BufferId::new(1);
        let version = BufferVersion::new(1);
        let text = "// TODO: Test invalidation";
        
        // Cache a result
        scanner.scan_buffer(buffer_id, version, text);
        
        // Invalidate buffer
        scanner.invalidate_buffer(buffer_id);
        
        // Next scan should miss cache
        scanner.scan_buffer(buffer_id, version, text);
        assert_eq!(scanner.cache_stats().misses, 2); // Initial miss + miss after invalidation
    }

    #[test]
    fn test_scan_file_convenience_function() {
        let text = r#"
        // TODO: Implement feature A
        /* FIXME: Fix feature B */
        // HACK: Temporary workaround
        "#;
        
        let matches = scan_file(text, "rust");
        assert_eq!(matches.len(), 3);
        
        let keywords: Vec<_> = matches.iter().map(|m| &m.keyword).collect();
        assert!(keywords.contains(&&"TODO".to_string()));
        assert!(keywords.contains(&&"FIXME".to_string()));
        assert!(keywords.contains(&&"HACK".to_string()));
    }

    #[test]
    fn test_scanner_multiple_buffers() {
        let mut scanner = WillowScanner::default();
        let buffer1 = BufferId::new(1);
        let buffer2 = BufferId::new(2);
        let version = BufferVersion::new(1);
        
        let text1 = "// TODO: Buffer 1";
        let text2 = "// FIXME: Buffer 2";
        
        let matches1 = scanner.scan_buffer(buffer1, version, text1);
        let matches2 = scanner.scan_buffer(buffer2, version, text2);
        
        assert_eq!(matches1.len(), 1);
        assert_eq!(matches1[0].keyword, "TODO");
        
        assert_eq!(matches2.len(), 1);
        assert_eq!(matches2[0].keyword, "FIXME");
    }

    #[test]
    fn test_scanner_empty_text() {
        let mut scanner = WillowScanner::default();
        let buffer_id = BufferId::new(1);
        let version = BufferVersion::new(1);
        let text = "";
        
        let matches = scanner.scan_buffer(buffer_id, version, text);
        assert!(matches.is_empty());
    }

    #[test]
    fn test_scanner_no_matches() {
        let mut scanner = WillowScanner::default();
        let buffer_id = BufferId::new(1);
        let version = BufferVersion::new(1);
        let text = "// Regular comment with no keywords";
        
        let matches = scanner.scan_buffer(buffer_id, version, text);
        assert!(matches.is_empty());
    }
}