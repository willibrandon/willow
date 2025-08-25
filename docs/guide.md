I'll search for the latest Zed extension API details to create an accurate implementation guide.Now let me search for information about what capabilities Zed extensions currently support, particularly around UI modifications and highlighting.Based on my research, I now have a comprehensive understanding of Zed's extension capabilities and limitations. Let me create the implementation guide for Willow.

---

# Willow Implementation Guide
## Building a TODO/FIXME Highlighter for Zed

**Version:** 1.0.0  
**Author:** willibrandon  
**Date:** January 2025

## Current State of Zed Extensions

Zed extensions are written in Rust and compiled to WebAssembly. Currently, extensions can add language support, debuggers, MCP servers, themes, and icon themes. The API doesn't yet support UI modifications or custom highlighting overlays, which means we need to work within these constraints.

## Project Setup

### 1. Prerequisites

```bash
# Install Rust via rustup (required)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# Install wasm target
rustup target add wasm32-wasip1

# Verify installation
rustc --version
cargo --version
```

### 2. Initialize Project Structure

```bash
# Create extension directory
mkdir willow-zed && cd willow-zed

# Initialize Git repository
git init

# Create directory structure
mkdir -p languages/todo-highlights
mkdir -p src
mkdir -p themes
```

### 3. Core Configuration Files

#### `extension.toml`
```toml
id = "willow"
name = "Willow - TODO Highlighter"
version = "0.1.0"
schema_version = 1
authors = ["willibrandon <your-email@example.com>"]
description = "Universal TODO/FIXME/HACK highlighting for all languages"
repository = "https://github.com/willibrandon/willow"

# Define a custom grammar for TODO patterns
[grammars.todo-injections]
repository = "https://github.com/willibrandon/tree-sitter-todo-injections"
commit = "main"
```

#### `Cargo.toml`
```toml
[package]
name = "willow"
version = "0.1.0"
edition = "2021"

[lib]
crate-type = ["cdylib"]

[dependencies]
zed_extension_api = "0.6.0"  # Latest as of research
serde = { version = "1.0", features = ["derive"] }
serde_json = "1.0"

[profile.release]
opt-level = "z"     # Optimize for size
lto = true          # Link-time optimization
codegen-units = 1   # Single codegen unit for smaller size
```

## Implementation Strategy

### Phase 1: Language Injection Approach

Since we can't modify UI directly, we'll use **tree-sitter language injection** to highlight TODOs across all languages.

#### `src/lib.rs`
```rust
use zed_extension_api as zed;
use serde::{Deserialize, Serialize};
use std::fs;

#[derive(Debug, Serialize, Deserialize)]
struct WillowConfig {
    patterns: Vec<TodoPattern>,
    enabled_languages: Vec<String>,
}

#[derive(Debug, Serialize, Deserialize)]
struct TodoPattern {
    keyword: String,
    priority: u8,
    style: String,
}

struct WillowExtension {
    config: WillowConfig,
}

impl WillowExtension {
    fn load_config() -> WillowConfig {
        // Load from config file or use defaults
        WillowConfig {
            patterns: vec![
                TodoPattern {
                    keyword: "TODO".to_string(),
                    priority: 1,
                    style: "info".to_string(),
                },
                TodoPattern {
                    keyword: "FIXME".to_string(),
                    priority: 2,
                    style: "warning".to_string(),
                },
                TodoPattern {
                    keyword: "HACK".to_string(),
                    priority: 3,
                    style: "error".to_string(),
                },
            ],
            enabled_languages: vec!["*".to_string()], // All languages
        }
    }
}

impl zed::Extension for WillowExtension {
    fn new() -> Self {
        Self {
            config: Self::load_config(),
        }
    }

    // Currently, we can't modify UI directly, but we can:
    // 1. Provide custom themes with TODO highlighting
    // 2. Use language injection for pattern matching
    // 3. Potentially provide a language server for diagnostics
}

zed::register_extension!(WillowExtension);
```

### Phase 2: Tree-sitter Grammar for TODO Injection

Create a custom tree-sitter grammar that can be injected into comments:

#### `tree-sitter-todo-injections/grammar.js`
```javascript
module.exports = grammar({
  name: 'todo_injections',

  extras: $ => [],

  rules: {
    source_file: $ => repeat($._item),

    _item: $ => choice(
      $.todo_item,
      $.fixme_item,
      $.hack_item,
      $.note_item,
      $.bug_item,
      $.optimize_item,
      $.deprecated_item,
      $.security_item
    ),

    todo_item: $ => seq(
      /\b(TODO|todo|Todo)\b/,
      optional(':'),
      optional($.message)
    ),

    fixme_item: $ => seq(
      /\b(FIXME|fixme|FixMe)\b/,
      optional(':'),
      optional($.message)
    ),

    hack_item: $ => seq(
      /\b(HACK|hack|Hack)\b/,
      optional(':'),
      optional($.message)
    ),

    note_item: $ => seq(
      /\b(NOTE|note|Note)\b/,
      optional(':'),
      optional($.message)
    ),

    bug_item: $ => seq(
      /\b(BUG|bug|Bug)\b/,
      optional(':'),
      optional($.message)
    ),

    optimize_item: $ => seq(
      /\b(OPTIMIZE|OPTIMI[SZ]E|optimi[sz]e)\b/,
      optional(':'),
      optional($.message)
    ),

    deprecated_item: $ => seq(
      /\b(DEPRECATED|deprecated|Deprecated)\b/,
      optional(':'),
      optional($.message)
    ),

    security_item: $ => seq(
      /\b(SECURITY|SEC|security|sec)\b/,
      optional(':'),
      optional($.message)
    ),

    message: $ => /.+/
  }
});
```

### Phase 3: Highlight Queries

Create highlight queries by copying them to `languages/todo-highlights/highlights.scm`:

#### `languages/todo-highlights/highlights.scm`
```scheme
; TODO patterns
(todo_item) @comment.todo
(todo_item (message) @comment.todo.message)

; FIXME patterns  
(fixme_item) @comment.fixme
(fixme_item (message) @comment.fixme.message)

; HACK patterns
(hack_item) @comment.hack
(hack_item (message) @comment.hack.message)

; NOTE patterns
(note_item) @comment.note
(note_item (message) @comment.note.message)

; BUG patterns
(bug_item) @comment.error
(bug_item (message) @comment.error.message)

; OPTIMIZE patterns
(optimize_item) @comment.optimize
(optimize_item (message) @comment.optimize.message)

; DEPRECATED patterns
(deprecated_item) @comment.deprecated
(deprecated_item (message) @comment.deprecated.message)

; SECURITY patterns
(security_item) @comment.security
(security_item (message) @comment.security.message)
```

### Phase 4: Custom Theme with TODO Highlighting

#### `themes/willow-dark.json`
```json
{
  "$schema": "https://zed.dev/schema/themes/v0.1.0.json",
  "name": "Willow Dark",
  "author": "willibrandon",
  "themes": [
    {
      "name": "Willow Dark",
      "appearance": "dark",
      "style": {
        "background": "#1e1e1e",
        "foreground": "#d4d4d4",
        "comment": "#608b4e",
        "comment.todo": "#4fc1ff",
        "comment.todo.message": "#4fc1ff",
        "comment.fixme": "#ffcc00",
        "comment.fixme.message": "#ffcc00",
        "comment.hack": "#ff6b6b",
        "comment.hack.message": "#ff6b6b",
        "comment.note": "#98c379",
        "comment.note.message": "#98c379",
        "comment.error": "#e06c75",
        "comment.error.message": "#e06c75",
        "comment.optimize": "#61afef",
        "comment.optimize.message": "#61afef",
        "comment.deprecated": "#7c7c7c",
        "comment.deprecated.message": "#7c7c7c",
        "comment.security": "#ff0000",
        "comment.security.message": "#ff0000"
      }
    }
  ]
}
```

## Development Workflow

### 1. Build Process

```bash
# Build the WebAssembly module
cargo build --release --target wasm32-wasip1

# The output will be at:
# target/wasm32-wasip1/release/willow.wasm
```

### 2. Testing Locally

Install as a dev extension by clicking "Install Dev Extension" in the extensions page and selecting your extension directory:

```bash
# Start Zed with debug output
zed --foreground

# In Zed:
# 1. Open command palette (Cmd+Shift+P)
# 2. Run "zed: extensions"
# 3. Click "Install Dev Extension"
# 4. Select the willow-zed directory
```

### 3. Debugging

```bash
# View logs
# In Zed: Run "zed: open log"

# Add debug output in Rust
println!("Debug: Processing pattern {:?}", pattern);
dbg!(&config);
```

## Alternative Approaches

### Approach 1: Language Server for Diagnostics

Instead of syntax highlighting, provide TODO items as diagnostics:

```rust
impl zed::Extension for WillowExtension {
    fn language_server_command(
        &mut self,
        _id: &zed::LanguageServerId,
        worktree: &zed::Worktree,
    ) -> Result<zed::Command, String> {
        Ok(zed::Command {
            command: "willow-lsp".to_string(),
            args: vec![],
            env: Default::default(),
        })
    }
}
```

### Approach 2: Multiple Language Definitions

Create separate language definitions for each file type with TODO patterns:

```toml
# languages/rust-with-todos/config.toml
name = "Rust with TODOs"
grammar = "rust-with-todos"
path_suffixes = ["rs"]
injection_regex = "rust"
```

## Publishing

### 1. Prepare for Release

```bash
# Update version in extension.toml and Cargo.toml
# Build final WASM
cargo build --release --target wasm32-wasip1

# Create GitHub repository
git remote add origin https://github.com/willibrandon/willow
git push -u origin main
```

### 2. Submit to Zed Extensions

1. Fork `zed-industries/extensions`
2. Add submodule:
   ```bash
   git submodule add https://github.com/willibrandon/willow extensions/willow
   ```
3. Update `extensions.toml`:
   ```toml
   [willow]
   submodule = "extensions/willow"
   version = "0.1.0"
   ```
4. Submit PR

## Performance Considerations

1. **WASM Size**: Keep under 1MB
   - Use `wee_alloc` for smaller allocator
   - Enable LTO and size optimizations
   - Minimize dependencies

2. **Pattern Matching**: 
   - Pre-compile regexes
   - Use quick string contains checks before regex
   - Cache results per buffer

3. **Memory Management**:
   - Use `Arc<str>` for shared strings
   - Implement buffer pooling
   - Clear caches on buffer close

## Future Enhancements

When Zed's extension API expands:

1. **Custom UI Panels**: TODO list sidebar
2. **Decorations API**: Inline highlighting
3. **Code Actions**: Quick-fix to remove TODOs
4. **Workspace Scanning**: Project-wide TODO search
5. **Git Integration**: Show TODO age via blame

## Troubleshooting

### Common Issues

1. **Extension not loading**:
   ```bash
   # Check Zed version compatibility
   zed --version
   
   # Verify WASM target
   rustup target list --installed | grep wasm32
   ```

2. **Highlighting not working**:
   - Ensure `highlights.scm` is in correct location
   - Check theme includes TODO token colors
   - Verify grammar is being loaded

3. **Performance issues**:
   - Reduce pattern complexity
   - Implement debouncing
   - Use incremental parsing

## Resources

- [Zed Extension Docs](https://zed.dev/docs/extensions)
- [Tree-sitter Documentation](https://tree-sitter.github.io/tree-sitter/)
- [WebAssembly Component Model](https://component-model.bytecodealliance.org/)
- [zed_extension_api Crate](https://crates.io/crates/zed_extension_api)

---

*This implementation guide provides a practical path forward within current Zed limitations while preparing for future API expansions. The key is starting with what's possible today—themes and language support—while architecting for tomorrow's capabilities.*