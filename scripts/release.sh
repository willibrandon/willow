#!/bin/bash

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

VERSION="${1:-}"
if [ -z "$VERSION" ]; then
    echo -e "${RED}Error: Version required${NC}"
    echo "Usage: $0 <version>"
    exit 1
fi

echo -e "${GREEN}Building release for Willow v$VERSION${NC}"

# Validate extension structure
echo -e "${YELLOW}Validating extension...${NC}"

if [ ! -f "extension.toml" ]; then
    echo -e "${RED}Error: extension.toml not found${NC}"
    exit 1
fi

if [ ! -d "languages" ]; then
    echo -e "${RED}Error: languages directory not found${NC}"
    exit 1
fi

if [ ! -d "languages/comment" ]; then
    echo -e "${RED}Error: languages/comment directory not found${NC}"
    exit 1
fi

# Count injections
INJECTION_COUNT=$(find languages -name "*-injections" -type d | wc -l | tr -d ' ')
echo -e "${GREEN}Found $INJECTION_COUNT language injections${NC}"

# Update version in extension.toml
echo -e "${YELLOW}Updating version in extension.toml...${NC}"
sed -i.bak "s/^version = .*/version = \"$VERSION\"/" extension.toml
rm -f extension.toml.bak

# Create dist directory
rm -rf dist
mkdir -p dist

# Create temp directory for packaging
TEMP_DIR=$(mktemp -d)
PACKAGE_DIR="$TEMP_DIR/willow"

echo -e "${YELLOW}Packaging extension...${NC}"

# Copy files
mkdir -p "$PACKAGE_DIR"
cp extension.toml "$PACKAGE_DIR/"
cp -r languages/ "$PACKAGE_DIR/"
cp README.md LICENSE "$PACKAGE_DIR/" 2>/dev/null || true

# Clean up unwanted files
find "$PACKAGE_DIR" -name ".DS_Store" -delete
find "$PACKAGE_DIR" -name "*.bak" -delete

# Create archives
cd "$TEMP_DIR"
tar -czf "willow-$VERSION.tar.gz" willow/
zip -qr "willow-$VERSION.zip" willow/
cd - > /dev/null

# Move to dist
mv "$TEMP_DIR/willow-$VERSION.tar.gz" dist/
mv "$TEMP_DIR/willow-$VERSION.zip" dist/

# Clean up
rm -rf "$TEMP_DIR"

echo -e "${GREEN}✓ Created dist/willow-$VERSION.tar.gz${NC}"
echo -e "${GREEN}✓ Created dist/willow-$VERSION.zip${NC}"

# Validate packages
echo -e "${YELLOW}Validating package...${NC}"
TEST_DIR=$(mktemp -d)
tar -xzf "dist/willow-$VERSION.tar.gz" -C "$TEST_DIR"

if [ ! -f "$TEST_DIR/willow/extension.toml" ]; then
    echo -e "${RED}Error: Package validation failed${NC}"
    exit 1
fi

if [ ! -d "$TEST_DIR/willow/languages" ]; then
    echo -e "${RED}Error: Package missing languages directory${NC}"
    exit 1
fi

rm -rf "$TEST_DIR"

echo -e "${GREEN}✓ Package validation passed${NC}"
echo -e "${GREEN}Release ready!${NC}"