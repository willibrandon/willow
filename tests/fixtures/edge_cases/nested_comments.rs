fn nested_comments() {
    /* Outer comment with TODO: nested item
     * /* This is a nested comment
     *    TODO: This should be detected
     *    FIXME: Handle nested properly
     * */
     * More outer comment text
     * HACK: After nested comment
     */
    
    // Line comment with /* block comment inside TODO: mixed styles */
    let x = 42;
    
    /* Multiple levels
     * /* Level 2
     *    /* Level 3 with TODO: deep nesting */
     *    FIXME: Back to level 2
     * */
     * Level 1 again with HACK: should work
     */
}

// Edge case: Comment markers in strings should not interfere
fn string_comments() {
    let code = r#"
        // TODO: This is in a raw string, not a comment
        /* FIXME: Also in string */
    "#;
    
    // TODO: But this is a real comment
    println!("{}", code);
    
    let regex = r"// TODO: regex pattern";
    // FIXME: The above string should not be highlighted
}

#[cfg(test)]
mod tests {
    // TODO: Add more test cases
    
    #[test]
    fn test_something() {
        /* FIXME: Implement this test
         * NOTE: Remember to test edge cases
         */
        assert!(true);
    }
}