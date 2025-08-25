# Willow 🌿

**A graceful TODO/FIXME highlighter for Zed - bending with your workflow, never breaking**

Willow is a TODO/FIXME highlighting extension for the Zed editor that uses tree-sitter grammar injection for language-agnostic comment highlighting.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Rust](https://img.shields.io/badge/rust-1.70+-orange.svg)
![Zed](https://img.shields.io/badge/zed-extension-green.svg)

## Features ✨

- **Universal Language Support**: Works with all Zed-supported languages using tree-sitter
- **Efficient Highlighting**: Tree-sitter grammar-based pattern recognition
- **Rich Pattern Recognition**: TODO, FIXME, HACK, NOTE, BUG, OPTIMIZE, SECURITY, and more
- **Beautiful Themes**: Custom dark and light themes with distinct highlighting
- **Unicode Support**: Handles international comments and emoji seamlessly
- **Zero Dependencies**: Pure tree-sitter grammar with no external tools required

## Supported Keywords 🏷️

| Keyword | Style | Priority | Description |
|---------|-------|----------|-------------|
| `TODO` | Info (Blue) | Medium | Tasks to be done |
| `FIXME` | Warning (Yellow) | Medium | Known issues to fix |
| `HACK` | Error (Red) | High | Temporary workarounds |
| `NOTE` | Success (Green) | Low | Important information |
| `BUG` | Error (Red) | High | Confirmed bugs |
| `OPTIMIZE` | Info (Blue) | Medium | Performance improvements |
| `SECURITY` | Critical (Red) | Critical | Security concerns |
| `DEPRECATED` | Muted (Gray) | Medium | Obsolete code |
| `REVIEW` | Purple | Medium | Code review needed |
| `REFACTOR` | Orange | Medium | Refactoring needed |

## Installation 📦

### From Zed Extensions (Coming Soon)

1. Open Zed
2. Run `zed: extensions` from the command palette
3. Search for "Willow"
4. Click Install

### Development Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/willibrandon/willow.git
   cd willow
   ```

2. Build the extension:
   ```bash
   ./scripts/build.sh
   ```

3. Install in Zed:
   ```bash
   ./scripts/dev.sh install
   ```

## Development 🛠️

### Prerequisites

- Rust 1.70+ with `wasm32-wasip1` target
- Zed editor
- (Optional) tree-sitter CLI for grammar development

### Quick Start

```bash
# Install Rust target
rustup target add wasm32-wasip1

# Clone and build
git clone https://github.com/willibrandon/willow.git
cd willow
./scripts/build.sh

# Run tests
./scripts/test.sh

# Development workflow
./scripts/dev.sh watch  # Auto-rebuild on changes
./scripts/dev.sh bench  # Run performance benchmarks
./scripts/dev.sh install  # Install in Zed
```

### Project Structure

```
willow/
├── src/                    # Extension configuration
│   ├── lib.rs             # Main extension entry point
│   ├── patterns.rs        # Pattern definitions
│   └── cache.rs           # Caching utilities
├── themes/                # Zed themes with TODO highlighting
│   ├── willow-dark.json   # Dark theme
│   └── willow-light.json  # Light theme
├── tree-sitter-todo-injections/  # Tree-sitter grammar for highlighting
├── languages/             # Language configuration
├── tests/                 # Test suite
├── benches/              # Benchmarks
└── scripts/              # Development tools
```

### Testing

```bash
# Run all tests
cargo test

# Run specific test categories
cargo test --test integration
cargo test --lib patterns

# Performance benchmarks
cargo bench

# Performance analysis
./scripts/performance-test.sh
```

### Build Targets 🎯

| Metric | Target | Status |
|--------|---------|---------|
| WASM binary size | <2MB | ✅ |
| Compilation time | <30s | ✅ |
| Grammar injection | All languages | ✅ |
| Theme compatibility | Dark/Light | ✅ |

## Architecture 🏗️

Willow uses tree-sitter grammar injection for syntax highlighting:

- **Grammar Injection**: Tree-sitter grammar that injects into comment nodes
- **Pattern Recognition**: Grammar-level keyword detection for TODO, FIXME, HACK, etc.
- **Theme Integration**: Custom highlighting rules integrated with Zed's theme system
- **Universal Support**: Works across all languages supported by Zed

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make changes with tests
4. Run `./scripts/test.sh`
5. Submit a pull request

## License

MIT License - see [LICENSE](LICENSE) file.
