//! High-performance caching system for TODO scan results
//! 
//! This module provides LRU caching with version tracking to avoid
//! re-scanning unchanged buffers.

use std::collections::HashMap;
use std::hash::Hash;
use std::time::Instant;
use crate::patterns::TodoMatch;

#[derive(Debug, Clone, Copy, Hash, Eq, PartialEq)]
pub struct BufferId(pub u64);

impl BufferId {
    pub fn new(id: u64) -> Self {
        Self(id)
    }
}

#[derive(Debug, Clone, Copy, Hash, Eq, PartialEq)]
pub struct BufferVersion(pub u64);

impl BufferVersion {
    pub fn new(version: u64) -> Self {
        Self(version)
    }
}

#[derive(Hash, Eq, PartialEq, Clone, Copy)]
struct BufferKey {
    buffer_id: BufferId,
    version: BufferVersion,
}

struct CachedResult {
    items: Vec<TodoMatch>,
    timestamp: Instant,
    access_count: u64,
}

#[derive(Debug, Default)]
pub struct CacheStats {
    pub hits: u64,
    pub misses: u64,
    pub evictions: u64,
    pub total_requests: u64,
}

impl CacheStats {
    pub fn hit_ratio(&self) -> f64 {
        if self.total_requests == 0 {
            0.0
        } else {
            self.hits as f64 / self.total_requests as f64
        }
    }
}

pub struct ResultCache {
    entries: HashMap<BufferKey, CachedResult>,
    max_size: usize,
    stats: CacheStats,
}

impl ResultCache {
    pub fn new(max_size: usize) -> Self {
        Self {
            entries: HashMap::with_capacity(max_size),
            max_size,
            stats: CacheStats::default(),
        }
    }

    pub fn get(&mut self, buffer_id: BufferId, version: BufferVersion) -> Option<Vec<TodoMatch>> {
        let key = BufferKey { buffer_id, version };
        self.stats.total_requests += 1;
        
        if let Some(cached) = self.entries.get_mut(&key) {
            self.stats.hits += 1;
            cached.access_count += 1;
            Some(cached.items.clone())
        } else {
            self.stats.misses += 1;
            None
        }
    }

    pub fn insert(&mut self, buffer_id: BufferId, version: BufferVersion, items: Vec<TodoMatch>) {
        let key = BufferKey { buffer_id, version };
        
        // If cache is full, evict least recently used entry
        if self.entries.len() >= self.max_size && !self.entries.contains_key(&key) {
            self.evict_lru();
        }
        
        let cached_result = CachedResult {
            items,
            timestamp: Instant::now(),
            access_count: 1,
        };
        
        self.entries.insert(key, cached_result);
    }

    pub fn invalidate_buffer(&mut self, buffer_id: BufferId) {
        // Remove all entries for this buffer (all versions)
        self.entries.retain(|key, _| key.buffer_id != buffer_id);
    }

    pub fn clear(&mut self) {
        self.entries.clear();
        self.stats = CacheStats::default();
    }

    pub fn stats(&self) -> &CacheStats {
        &self.stats
    }

    pub fn len(&self) -> usize {
        self.entries.len()
    }

    pub fn is_empty(&self) -> bool {
        self.entries.is_empty()
    }

    fn evict_lru(&mut self) {
        // Find entry with lowest access count, then oldest timestamp
        let oldest_key = self.entries
            .iter()
            .min_by_key(|(_, cached)| (cached.access_count, cached.timestamp))
            .map(|(key, _)| *key);
        
        if let Some(key) = oldest_key {
            self.entries.remove(&key);
            self.stats.evictions += 1;
        }
    }
}

impl Default for ResultCache {
    fn default() -> Self {
        Self::new(100) // Default cache size of 100 buffers
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::patterns::{TodoMatch, HighlightStyle};

    fn create_test_todo(keyword: &str, message: &str) -> TodoMatch {
        TodoMatch {
            keyword: keyword.to_string(),
            message: message.to_string(),
            start: 0,
            end: keyword.len(),
            priority: 1,
            style: HighlightStyle::Info,
        }
    }

    #[test]
    fn test_cache_basic_operations() {
        let mut cache = ResultCache::new(10);
        let buffer_id = BufferId::new(1);
        let version = BufferVersion::new(1);
        let items = vec![create_test_todo("TODO", "Test")];
        
        // Miss initially
        assert!(cache.get(buffer_id, version).is_none());
        assert_eq!(cache.stats().misses, 1);
        
        // Insert and hit
        cache.insert(buffer_id, version, items.clone());
        let result = cache.get(buffer_id, version);
        assert!(result.is_some());
        assert_eq!(result.unwrap().len(), 1);
        assert_eq!(cache.stats().hits, 1);
        
        // Hit ratio
        assert_eq!(cache.stats().hit_ratio(), 0.5); // 1 hit out of 2 total
    }

    #[test]
    fn test_cache_version_invalidation() {
        let mut cache = ResultCache::new(10);
        let buffer_id = BufferId::new(1);
        let version1 = BufferVersion::new(1);
        let version2 = BufferVersion::new(2);
        let items = vec![create_test_todo("TODO", "Test")];
        
        cache.insert(buffer_id, version1, items.clone());
        assert!(cache.get(buffer_id, version1).is_some());
        
        // Different version should miss
        assert!(cache.get(buffer_id, version2).is_none());
    }

    #[test]
    fn test_cache_eviction() {
        let mut cache = ResultCache::new(2);
        let items = vec![create_test_todo("TODO", "Test")];
        
        cache.insert(BufferId::new(1), BufferVersion::new(1), items.clone());
        cache.insert(BufferId::new(2), BufferVersion::new(1), items.clone());
        
        // Cache should be full
        assert_eq!(cache.len(), 2);
        
        // Adding third item should trigger eviction
        cache.insert(BufferId::new(3), BufferVersion::new(1), items.clone());
        assert_eq!(cache.len(), 2);
        assert_eq!(cache.stats().evictions, 1);
    }

    #[test]
    fn test_buffer_invalidation() {
        let mut cache = ResultCache::new(10);
        let buffer_id = BufferId::new(1);
        let items = vec![create_test_todo("TODO", "Test")];
        
        // Insert multiple versions of same buffer
        cache.insert(buffer_id, BufferVersion::new(1), items.clone());
        cache.insert(buffer_id, BufferVersion::new(2), items.clone());
        cache.insert(BufferId::new(2), BufferVersion::new(1), items.clone());
        
        assert_eq!(cache.len(), 3);
        
        // Invalidate buffer 1
        cache.invalidate_buffer(buffer_id);
        
        // Should only have buffer 2 left
        assert_eq!(cache.len(), 1);
        assert!(cache.get(BufferId::new(2), BufferVersion::new(1)).is_some());
        assert!(cache.get(buffer_id, BufferVersion::new(1)).is_none());
    }

    #[test]
    fn test_lru_eviction_order() {
        let mut cache = ResultCache::new(2);
        let items = vec![create_test_todo("TODO", "Test")];
        
        // Insert two items
        cache.insert(BufferId::new(1), BufferVersion::new(1), items.clone());
        std::thread::sleep(std::time::Duration::from_millis(1)); // Ensure different timestamps
        cache.insert(BufferId::new(2), BufferVersion::new(1), items.clone());
        
        // Access first item to increase its access count
        cache.get(BufferId::new(1), BufferVersion::new(1));
        
        // Insert third item - should evict buffer 2 (lower access count)
        cache.insert(BufferId::new(3), BufferVersion::new(1), items.clone());
        
        // Buffer 1 should still be there, buffer 2 should be evicted
        assert!(cache.get(BufferId::new(1), BufferVersion::new(1)).is_some());
        assert!(cache.get(BufferId::new(2), BufferVersion::new(1)).is_none());
        assert!(cache.get(BufferId::new(3), BufferVersion::new(1)).is_some());
    }

    #[test]
    fn test_cache_stats() {
        let mut cache = ResultCache::new(5);
        let buffer_id = BufferId::new(1);
        let version = BufferVersion::new(1);
        let items = vec![create_test_todo("TODO", "Test")];
        
        // Initial stats
        assert_eq!(cache.stats().hits, 0);
        assert_eq!(cache.stats().misses, 0);
        assert_eq!(cache.stats().total_requests, 0);
        assert_eq!(cache.stats().hit_ratio(), 0.0);
        
        // Miss
        cache.get(buffer_id, version);
        assert_eq!(cache.stats().misses, 1);
        assert_eq!(cache.stats().total_requests, 1);
        
        // Insert and hit
        cache.insert(buffer_id, version, items);
        cache.get(buffer_id, version);
        assert_eq!(cache.stats().hits, 1);
        assert_eq!(cache.stats().total_requests, 2);
        assert_eq!(cache.stats().hit_ratio(), 0.5);
    }

    #[test]
    fn test_cache_clear() {
        let mut cache = ResultCache::new(10);
        let items = vec![create_test_todo("TODO", "Test")];
        
        cache.insert(BufferId::new(1), BufferVersion::new(1), items);
        cache.get(BufferId::new(1), BufferVersion::new(1));
        
        assert!(!cache.is_empty());
        assert!(cache.stats().total_requests > 0);
        
        cache.clear();
        
        assert!(cache.is_empty());
        assert_eq!(cache.stats().total_requests, 0);
        assert_eq!(cache.stats().hits, 0);
        assert_eq!(cache.stats().misses, 0);
    }
}