#!/bin/bash
set -e

echo "🌿 Willow Development Environment"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to show usage
show_usage() {
    echo -e "${BLUE}Usage: $0 [command]${NC}"
    echo -e ""
    echo -e "Available commands:"
    echo -e "  ${GREEN}build${NC}     - Build the extension"
    echo -e "  ${GREEN}test${NC}      - Run all tests"
    echo -e "  ${GREEN}bench${NC}     - Run benchmarks"
    echo -e "  ${GREEN}watch${NC}     - Watch for changes and rebuild"
    echo -e "  ${GREEN}install${NC}   - Install in Zed (dev extension)"
    echo -e "  ${GREEN}clean${NC}     - Clean build artifacts"
    echo -e "  ${GREEN}lint${NC}      - Run linting checks"
    echo -e "  ${GREEN}format${NC}    - Format code"
    echo -e "  ${GREEN}check${NC}     - Quick compile check"
    echo -e "  ${GREEN}docs${NC}      - Generate documentation"
    echo -e ""
    echo -e "If no command is provided, will run ${GREEN}build${NC} by default."
}

# Default to build if no argument provided
COMMAND=${1:-build}

case $COMMAND in
    "build")
        echo -e "${YELLOW}Building Willow extension...${NC}"
        ./scripts/build.sh
        ;;
    
    "test")
        echo -e "${YELLOW}Running test suite...${NC}"
        ./scripts/test.sh
        ;;
    
    "bench")
        echo -e "${YELLOW}Running benchmarks...${NC}"
        echo -e "${BLUE}Pattern matching performance:${NC}"
        cargo bench --bench pattern_matching -- --quick
        echo -e "\n${BLUE}Cache performance:${NC}"
        cargo bench --bench cache_performance -- --quick
        ;;
    
    "watch")
        if ! command -v cargo-watch &> /dev/null; then
            echo -e "${YELLOW}Installing cargo-watch...${NC}"
            cargo install cargo-watch
        fi
        
        echo -e "${YELLOW}Watching for changes...${NC}"
        cargo watch -x "check --target wasm32-wasip1" -x "test --lib"
        ;;
    
    "install")
        echo -e "${YELLOW}Installing Willow as dev extension in Zed...${NC}"
        
        # Build first
        ./scripts/build.sh
        
        # Check if Zed is available
        if ! command -v zed &> /dev/null; then
            echo -e "${RED}Error: Zed not found. Please install Zed first.${NC}"
            exit 1
        fi
        
        # Kill any running Zed instances
        pkill -f "Zed" 2>/dev/null || true
        
        echo -e "${BLUE}Starting Zed with extension...${NC}"
        echo -e "1. In Zed, open command palette (Cmd+Shift+P)"
        echo -e "2. Run 'zed: extensions'"
        echo -e "3. Click 'Install Dev Extension'"
        echo -e "4. Select this directory: $(pwd)"
        
        # Start Zed in background
        nohup zed --foreground > /dev/null 2>&1 &
        
        # Open test files
        sleep 2
        zed tests/fixtures/sample_code/ 2>/dev/null || true
        
        echo -e "${GREEN}✓ Zed started with test files${NC}"
        ;;
    
    "clean")
        echo -e "${YELLOW}Cleaning build artifacts...${NC}"
        cargo clean
        
        if [ -d "tree-sitter-todo-injections/src" ]; then
            echo -e "${YELLOW}Cleaning tree-sitter artifacts...${NC}"
            cd tree-sitter-todo-injections
            rm -rf src/*.c src/*.h node_modules build
            cd ..
        fi
        
        echo -e "${GREEN}✓ Clean completed${NC}"
        ;;
    
    "lint")
        echo -e "${YELLOW}Running linting checks...${NC}"
        
        # Clippy lints
        cargo clippy --all-targets --all-features -- -D warnings
        
        # Check formatting
        cargo fmt -- --check
        
        echo -e "${GREEN}✓ Linting completed${NC}"
        ;;
    
    "format")
        echo -e "${YELLOW}Formatting code...${NC}"
        cargo fmt
        echo -e "${GREEN}✓ Code formatted${NC}"
        ;;
    
    "check")
        echo -e "${YELLOW}Running quick compile check...${NC}"
        cargo check --all-targets
        cargo check --target wasm32-wasip1
        echo -e "${GREEN}✓ Compile check completed${NC}"
        ;;
    
    "docs")
        echo -e "${YELLOW}Generating documentation...${NC}"
        cargo doc --no-deps --open
        echo -e "${GREEN}✓ Documentation generated${NC}"
        ;;
    
    "help" | "-h" | "--help")
        show_usage
        ;;
    
    *)
        echo -e "${RED}Unknown command: $COMMAND${NC}"
        show_usage
        exit 1
        ;;
esac