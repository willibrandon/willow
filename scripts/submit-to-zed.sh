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

# Delete existing branch if it exists
git push origin --delete "$BRANCH_NAME" 2>/dev/null || true

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
    echo "Updated existing willow entry to version $VERSION"
else
    # Add new entry
    echo "" >> extensions.toml
    echo "[willow]" >> extensions.toml
    echo "version = \"$VERSION\"" >> extensions.toml
    echo "Added new willow entry with version $VERSION"
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

# Wait a moment for GitHub to process the push
sleep 5

# Verify the branch exists on the remote
echo "Verifying branch exists on remote..."
git ls-remote origin "$BRANCH_NAME" || {
    echo -e "${RED}Branch $BRANCH_NAME not found on remote${NC}"
    exit 1
}

# Debug: Check what changes we have
echo "Checking differences between main and our branch..."
git diff upstream/main..HEAD --name-only
echo "Checking commit log..."
git log upstream/main..HEAD --oneline

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

# Try creating the PR from the fork's perspective
cd ../
gh repo clone "$FORK_OWNER/extensions" fork-extensions
cd fork-extensions
git checkout "$BRANCH_NAME"

PR_URL=$(gh pr create \
    --repo "$EXTENSIONS_REPO" \
    --base "main" \
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