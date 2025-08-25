#!/bin/bash
set -e

echo "🌿 Building Willow TODO Highlighter Extension"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# This extension doesn't need compilation - it's pure tree-sitter configuration
echo -e "${GREEN}✓ Extension ready!${NC}"
echo ""
echo "To install in Zed:"
echo "  1. Open Zed"
echo "  2. Cmd+Shift+P → 'Install Dev Extension'"
echo "  3. Select this directory"