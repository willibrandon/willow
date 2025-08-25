#!/bin/bash
set -e

echo "🌿 Building Willow TODO Highlighter Extension"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Check prerequisites
echo -e "${YELLOW}Checking prerequisites...${NC}"

if ! command -v cargo &> /dev/null; then
    echo -e "${RED}Error: cargo not found. Please install Rust.${NC}"
    exit 1
fi

if ! command -v rustc &> /dev/null; then
    echo -e "${RED}Error: rustc not found. Please install Rust.${NC}"
    exit 1
fi

# Check if wasm32-wasip1 target is installed
if ! rustup target list --installed | grep -q "wasm32-wasip1"; then
    echo -e "${YELLOW}Installing wasm32-wasip1 target...${NC}"
    rustup target add wasm32-wasip1
fi

# Clean previous builds
echo -e "${YELLOW}Cleaning previous builds...${NC}"
cargo clean

# Run tests first (build with test profile)
echo -e "${YELLOW}Running tests...${NC}"
cargo test --lib --quiet
if [ $? -ne 0 ]; then
    echo -e "${RED}Tests failed. Build aborted.${NC}"
    exit 1
fi

# Build WebAssembly for Zed extension
echo -e "${YELLOW}Building WebAssembly extension...${NC}"
cargo build --release --target wasm32-wasip1

# Check if build was successful
if [ ! -f "target/wasm32-wasip1/release/willow.wasm" ]; then
    echo -e "${RED}WebAssembly build failed!${NC}"
    exit 1
fi

# Get WASM file size
WASM_SIZE=$(stat -f%z target/wasm32-wasip1/release/willow.wasm 2>/dev/null || stat -c%s target/wasm32-wasip1/release/willow.wasm)
WASM_SIZE_KB=$((WASM_SIZE / 1024))

echo -e "${GREEN}✓ Build completed successfully!${NC}"
echo -e "📦 WebAssembly size: ${WASM_SIZE_KB}KB"

# Warn if WASM is too large
if [ $WASM_SIZE -gt 1048576 ]; then  # 1MB
    echo -e "${YELLOW}⚠️  Warning: WASM size exceeds 1MB. Consider optimizing.${NC}"
else
    echo -e "${GREEN}✓ WASM size is within limits${NC}"
fi

# Build tree-sitter grammar if available
if [ -d "tree-sitter-todo-injections" ] && command -v tree-sitter &> /dev/null; then
    echo -e "${YELLOW}Building tree-sitter grammar...${NC}"
    cd tree-sitter-todo-injections
    
    if tree-sitter generate; then
        echo -e "${GREEN}✓ Tree-sitter grammar built successfully${NC}"
    else
        echo -e "${YELLOW}⚠️  Tree-sitter grammar build failed (non-critical)${NC}"
    fi
    
    cd ..
fi

# Copy extension files to target directory for easy installation
echo -e "${YELLOW}Copying extension files to target directory...${NC}"
cp extension.toml target/wasm32-wasip1/release/
cp -r languages target/wasm32-wasip1/release/
cp -r themes target/wasm32-wasip1/release/
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Extension files copied successfully${NC}"
else
    echo -e "${YELLOW}⚠️  Failed to copy extension files${NC}"
fi

echo -e "${GREEN}🎉 Willow extension build complete!${NC}"
echo "Ready for Zed installation:"
echo "  - WASM: target/wasm32-wasip1/release/willow.wasm"
echo "  - Config: target/wasm32-wasip1/release/extension.toml"