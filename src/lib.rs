//! Willow - Universal TODO/FIXME/HACK highlighter for Zed
//! 
//! This extension provides syntax highlighting for TODO, FIXME, HACK, and other
//! comment-based annotations across all programming languages supported by Zed.

use zed_extension_api as zed;

mod patterns;
mod cache;
mod scanner;

pub use patterns::{PatternMatcher, TodoPattern, TodoMatch, HighlightStyle};
pub use cache::{ResultCache, BufferId, BufferVersion};
pub use scanner::{WillowScanner, scan_file};

use serde::{Deserialize, Serialize};
use serde_json;

#[derive(Debug, Serialize, Deserialize)]
struct WillowConfig {
    patterns: Vec<TodoPattern>,
    enabled_languages: Vec<String>,
    enabled: bool,
    scan_on_save: bool,
    scan_on_type: bool,
    debounce_ms: u64,
}

impl Default for WillowConfig {
    fn default() -> Self {
        Self {
            patterns: PatternMatcher::default_patterns(),
            enabled_languages: vec!["*".to_string()], // All languages
            enabled: true,
            scan_on_save: true,
            scan_on_type: true,
            debounce_ms: 500,
        }
    }
}

struct WillowExtension {
    config: WillowConfig,
}

impl WillowExtension {
    fn load_config() -> WillowConfig {
        // TODO: Load from config file in future version
        // For now, use defaults
        WillowConfig::default()
    }
}

impl zed::Extension for WillowExtension {
    fn new() -> Self {
        let config = Self::load_config();
        
        Self {
            config,
        }
    }

    fn language_server_command(
        &mut self,
        _language_server_id: &zed::LanguageServerId,
        _worktree: &zed::Worktree,
    ) -> Result<zed::Command, String> {
        // For now, we don't provide a language server
        // The highlighting will be handled through tree-sitter injection
        Err("No language server provided".to_string())
    }

    fn language_server_initialization_options(
        &mut self,
        _language_server_id: &zed::LanguageServerId,
        _worktree: &zed::Worktree,
    ) -> Result<Option<zed::serde_json::Value>, String> {
        // No initialization options needed for now
        Ok(None)
    }

    fn language_server_workspace_configuration(
        &mut self,
        _language_server_id: &zed::LanguageServerId,
        _worktree: &zed::Worktree,
    ) -> Result<Option<zed::serde_json::Value>, String> {
        // Return configuration that could be used by a future language server
        let config_json = serde_json::json!({
            "patterns": self.config.patterns,
            "enabled": self.config.enabled,
            "scan_on_save": self.config.scan_on_save,
            "scan_on_type": self.config.scan_on_type,
            "debounce_ms": self.config.debounce_ms
        });
        Ok(Some(config_json))
    }
}

zed::register_extension!(WillowExtension);