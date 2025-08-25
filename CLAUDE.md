# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Willow is a TODO/FIXME highlighter extension for the Zed editor. The project is in the design and planning phase, with comprehensive documentation outlining the architecture and implementation approach for a tree-sitter-based highlighting system.

## Architecture

This is a documentation-only repository containing three main design documents:

- **docs/design.md** - Complete technical design including architecture, components, performance targets, and implementation phases
- **docs/guide.md** - Step-by-step implementation guide with practical examples and code samples  
- **docs/testing-guide.md** - Comprehensive testing strategy covering unit tests, integration tests, benchmarks, and manual testing

The design follows a modular architecture with these key components:
- **Scanner Module** - Tree-sitter based comment extraction with regex fallback
- **Pattern Registry** - Configurable TODO/FIXME/HACK pattern matching
- **Cache System** - LRU caching for performance optimization
- **Language Support** - Universal language support via tree-sitter queries
- **UI Integration** - Theme-based highlighting within Zed's constraints

## Development Commands

This is currently a documentation-only project with no build system or code implementation yet. Based on the design documents, the planned implementation will use:

```bash
# Future Rust/WASM build commands (not yet implemented)
cargo build --release --target wasm32-wasip1
cargo test
cargo bench

# Tree-sitter grammar testing (planned)
tree-sitter generate
tree-sitter test
```

## Key Implementation Constraints

- Zed extensions run as WebAssembly modules compiled from Rust
- Current Zed API limitations mean UI highlighting must be achieved through language injection and themes
- Performance targets: <10ms for 1K LOC files, <50ms for 10K LOC files
- Must support all languages Zed supports through tree-sitter queries with regex fallback

## Development Workflow

1. Review design documents in docs/ directory to understand architecture
2. Implementation will follow the phases outlined in docs/design.md
3. Testing approach detailed in docs/testing-guide.md covers unit, integration, and performance testing
4. Manual testing requires Zed installation and dev extension loading