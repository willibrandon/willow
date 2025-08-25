#!/bin/bash

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

ERRORS=0
WARNINGS=0

echo -e "${GREEN}Validating Willow Extension${NC}"
echo "================================"

# Check required files
echo -e "\n${YELLOW}Checking required files...${NC}"

if [ ! -f "extension.toml" ]; then
    echo -e "${RED}✗ extension.toml missing${NC}"
    ((ERRORS++))
else
    echo -e "${GREEN}✓ extension.toml found${NC}"
fi

if [ ! -d "languages" ]; then
    echo -e "${RED}✗ languages directory missing${NC}"
    ((ERRORS++))
else
    echo -e "${GREEN}✓ languages directory found${NC}"
fi

if [ ! -d "languages/comment" ]; then
    echo -e "${RED}✗ languages/comment directory missing${NC}"
    ((ERRORS++))
else
    echo -e "${GREEN}✓ languages/comment found${NC}"
fi

if [ ! -f "languages/comment/highlights.scm" ]; then
    echo -e "${RED}✗ languages/comment/highlights.scm missing${NC}"
    ((ERRORS++))
else
    echo -e "${GREEN}✓ languages/comment/highlights.scm found${NC}"
fi

# Check language injections
echo -e "\n${YELLOW}Checking language injections...${NC}"

EXPECTED_LANGS=("rust" "javascript" "typescript" "python" "go" "cpp" "java" "ruby" "swift" "kotlin" "php" "c_sharp" "elixir" "haskell")
FOUND_LANGS=0

for lang in "${EXPECTED_LANGS[@]}"; do
    if [ -d "languages/${lang}-injections" ]; then
        if [ -f "languages/${lang}-injections/injections.scm" ]; then
            echo -e "${GREEN}✓ ${lang}-injections found${NC}"
            ((FOUND_LANGS++))
        else
            echo -e "${RED}✗ ${lang}-injections missing injections.scm${NC}"
            ((ERRORS++))
        fi
    else
        echo -e "${YELLOW}⚠ ${lang}-injections not found${NC}"
        ((WARNINGS++))
    fi
done

echo -e "${GREEN}Found $FOUND_LANGS/$((${#EXPECTED_LANGS[@]})) language injections${NC}"

# Validate extension.toml
echo -e "\n${YELLOW}Validating extension.toml...${NC}"

if grep -q '^id = "willow"' extension.toml; then
    echo -e "${GREEN}✓ Extension ID correct${NC}"
else
    echo -e "${RED}✗ Extension ID incorrect or missing${NC}"
    ((ERRORS++))
fi

if grep -q '^version = ' extension.toml; then
    VERSION=$(grep '^version = ' extension.toml | sed 's/version = "\(.*\)"/\1/')
    echo -e "${GREEN}✓ Version found: $VERSION${NC}"
else
    echo -e "${RED}✗ Version missing${NC}"
    ((ERRORS++))
fi

# Check for grammar configuration
if grep -q '\[grammars.comment\]' extension.toml; then
    echo -e "${GREEN}✓ Comment grammar configured${NC}"
else
    echo -e "${RED}✗ Comment grammar not configured${NC}"
    ((ERRORS++))
fi

# Check for unnecessary files
echo -e "\n${YELLOW}Checking for unnecessary files...${NC}"

if [ -d "src" ]; then
    echo -e "${YELLOW}⚠ src directory found (not needed for pure config extension)${NC}"
    ((WARNINGS++))
fi

if [ -f "Cargo.toml" ]; then
    echo -e "${YELLOW}⚠ Cargo.toml found (not needed for pure config extension)${NC}"
    ((WARNINGS++))
fi

if [ -d "target" ]; then
    echo -e "${YELLOW}⚠ target directory found (build artifact)${NC}"
    ((WARNINGS++))
fi

# Check highlights.scm patterns
echo -e "\n${YELLOW}Checking highlight patterns...${NC}"

PATTERNS=("TODO" "FIXME" "HACK" "NOTE" "WARNING")
for pattern in "${PATTERNS[@]}"; do
    if grep -q "\"$pattern\"" languages/comment/highlights.scm; then
        echo -e "${GREEN}✓ $pattern pattern found${NC}"
    else
        echo -e "${YELLOW}⚠ $pattern pattern not found${NC}"
        ((WARNINGS++))
    fi
done

# Summary
echo -e "\n================================"
if [ $ERRORS -eq 0 ]; then
    if [ $WARNINGS -eq 0 ]; then
        echo -e "${GREEN}✓ Validation passed with no issues!${NC}"
    else
        echo -e "${GREEN}✓ Validation passed with $WARNINGS warnings${NC}"
    fi
    exit 0
else
    echo -e "${RED}✗ Validation failed with $ERRORS errors and $WARNINGS warnings${NC}"
    exit 1
fi