#!/bin/bash

# Helper function to create language injection
create_injection() {
    local lang_name=$1
    local grammar=$2
    local suffixes=$3
    local injection_pattern=$4
    
    dir="languages/${grammar}-injections"
    mkdir -p "$dir"
    
    # Create config.toml
    cat > "$dir/config.toml" << EOF
name = "${lang_name} with TODOs"
grammar = "${grammar}"
path_suffixes = [${suffixes}]
EOF
    
    # Create injections.scm
    echo "$injection_pattern" > "$dir/injections.scm"
    
    echo "✓ Added support for ${lang_name}"
}

# Python
create_injection "Python" "python" '"py", "pyw"' \
'((comment) @injection.content
 (#set! injection.language "comment"))'

# Go
create_injection "Go" "go" '"go"' \
'((comment) @injection.content
 (#set! injection.language "comment"))'

# C
create_injection "C" "c" '"c", "h"' \
'([(comment) (block_comment)] @injection.content
 (#set! injection.language "comment"))'

# C++
create_injection "C++" "cpp" '"cpp", "cc", "cxx", "hpp", "hh", "hxx"' \
'([(comment) (block_comment)] @injection.content
 (#set! injection.language "comment"))'

# Java
create_injection "Java" "java" '"java"' \
'([(line_comment) (block_comment)] @injection.content
 (#set! injection.language "comment"))'

# Ruby
create_injection "Ruby" "ruby" '"rb"' \
'((comment) @injection.content
 (#set! injection.language "comment"))'

# Shell
create_injection "Shell" "bash" '"sh", "bash", "zsh"' \
'((comment) @injection.content
 (#set! injection.language "comment"))'

# YAML
create_injection "YAML" "yaml" '"yml", "yaml"' \
'((comment) @injection.content
 (#set! injection.language "comment"))'

# TOML
create_injection "TOML" "toml" '"toml"' \
'((comment) @injection.content
 (#set! injection.language "comment"))'

# JSON (no comments, but JSON5 has them)
create_injection "JSON5" "json5" '"json5"' \
'((comment) @injection.content
 (#set! injection.language "comment"))'

echo ""
echo "All language injections created!"