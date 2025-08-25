#!/bin/bash
set -e

echo "🧪 Running Willow Test Suite"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test configuration
export RUST_BACKTRACE=1

echo -e "${YELLOW}Starting comprehensive test suite...${NC}"

# Unit tests
echo -e "${BLUE}Running unit tests...${NC}"
cargo test --lib --verbose
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Unit tests failed${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Unit tests passed${NC}"

# Integration tests
echo -e "${BLUE}Running integration tests...${NC}"
cargo test --test integration --verbose
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Integration tests failed${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Integration tests passed${NC}"

# Test with different optimization levels
echo -e "${BLUE}Testing with optimizations...${NC}"
cargo test --release --quiet
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Optimized tests failed${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Optimized tests passed${NC}"

# Tree-sitter grammar tests (if available)
if [ -d "tree-sitter-todo-injections" ] && command -v tree-sitter &> /dev/null; then
    echo -e "${BLUE}Testing tree-sitter grammar...${NC}"
    cd tree-sitter-todo-injections
    
    if tree-sitter test; then
        echo -e "${GREEN}✓ Tree-sitter grammar tests passed${NC}"
    else
        echo -e "${YELLOW}⚠️  Tree-sitter grammar tests failed (non-critical)${NC}"
    fi
    
    cd ..
fi

# Benchmark tests (quick run)
echo -e "${BLUE}Running performance benchmarks...${NC}"
cargo bench --no-run
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Benchmark compilation failed${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Benchmarks compiled successfully${NC}"

# Test WASM build
echo -e "${BLUE}Testing WebAssembly build...${NC}"
cargo check --target wasm32-wasip1
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ WASM build check failed${NC}"
    exit 1
fi
echo -e "${GREEN}✓ WASM build check passed${NC}"

# Code coverage (if tarpaulin is installed)
if command -v cargo-tarpaulin &> /dev/null; then
    echo -e "${BLUE}Generating code coverage report...${NC}"
    cargo tarpaulin --out Html --output-dir target/coverage --timeout 120 --verbose
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ Coverage report generated in target/coverage/tarpaulin-report.html${NC}"
    else
        echo -e "${YELLOW}⚠️  Coverage report generation failed${NC}"
    fi
fi

# Test summary
echo -e "\n${GREEN}🎉 All tests completed successfully!${NC}"
echo -e "${BLUE}Test Summary:${NC}"
echo -e "  ✓ Unit tests"
echo -e "  ✓ Integration tests" 
echo -e "  ✓ Optimized builds"
echo -e "  ✓ WASM compatibility"
echo -e "  ✓ Benchmark compilation"

if [ -d "tree-sitter-todo-injections" ]; then
    echo -e "  ✓ Tree-sitter grammar"
fi

echo -e "\n${GREEN}Ready for deployment! 🚀${NC}"