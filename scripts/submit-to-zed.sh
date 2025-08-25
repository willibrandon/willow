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

# Configuration
EXTENSIONS_REPO="zed-industries/extensions"
MY_REPO="willibrandon/willow"
BRANCH_NAME="willow-v$VERSION"

echo -e "${GREEN}Submitting Willow v$VERSION to Zed Extensions${NC}"

# Check for GitHub CLI
if ! command -v gh &> /dev/null; then
    echo -e "${RED}Error: GitHub CLI (gh) is required${NC}"
    echo "Install from: https://cli.github.com"
    exit 1
fi

# Create temp directory
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"

echo -e "${YELLOW}Forking and cloning extensions repo...${NC}"

# Fork if needed (will skip if already forked)
gh repo fork "$EXTENSIONS_REPO" --clone=false 2>/dev/null || true

# Get the fork owner (current authenticated user)
FORK_OWNER=$(gh api user --jq .login)

# Clone the fork using token authentication
git clone "https://$GITHUB_TOKEN@github.com/$FORK_OWNER/extensions.git" extensions
cd extensions

# Add upstream remote
git remote add upstream "https://github.com/$EXTENSIONS_REPO.git"
git fetch upstream

# Create new branch from upstream/main
git checkout -b "$BRANCH_NAME" upstream/main

echo -e "${YELLOW}Adding Willow as submodule...${NC}"

# Add Willow as submodule
git submodule add "https://github.com/$MY_REPO.git" extensions/willow

# Update extensions.toml
echo -e "${YELLOW}Updating extensions.toml...${NC}"

# Check if willow already exists in extensions.toml
if grep -q '^\[willow\]' extensions.toml; then
    # Update existing entry
    sed -i.bak "/^\[willow\]/,/^$/s/version = .*/version = \"$VERSION\"/" extensions.toml
else
    # Add new entry
    cat >> extensions.toml << EOF

[willow]
version = "$VERSION"
EOF
fi

rm -f extensions.toml.bak

# Commit changes
echo -e "${YELLOW}Committing changes...${NC}"
git config user.name "github-actions[bot]"
git config user.email "github-actions[bot]@users.noreply.github.com"
git add .
git commit -m "Add Willow v$VERSION - TODO/FIXME highlighter

Willow provides syntax highlighting for TODO, FIXME, HACK, and other
comment markers across all languages in Zed."

# Push to fork
echo -e "${YELLOW}Pushing to fork...${NC}"
git remote set-url origin "https://$GITHUB_TOKEN@github.com/$FORK_OWNER/extensions.git"
git push origin "$BRANCH_NAME"

# Create PR
echo -e "${YELLOW}Creating pull request...${NC}"

PR_BODY="## Willow v$VERSION

TODO/FIXME highlighter extension for Zed.

### Features
- Highlights TODO, FIXME, HACK, NOTE, WARNING, and other markers
- Works across all languages
- Customizable through themes
- Zero configuration required

### Testing
- Tested on macOS and Linux
- Validated with multiple languages
- Performance tested with large files"

PR_URL=$(gh pr create \
    --repo "$EXTENSIONS_REPO" \
    --head "$FORK_OWNER:$BRANCH_NAME" \
    --title "Add Willow v$VERSION - TODO/FIXME highlighter" \
    --body "$PR_BODY")

# Clean up
cd /
rm -rf "$TEMP_DIR"

if [ -n "$PR_URL" ]; then
    echo -e "${GREEN}✓ Pull request created successfully: $PR_URL${NC}"
else
    echo -e "${RED}✗ Failed to create pull request${NC}"
    exit 1
fi