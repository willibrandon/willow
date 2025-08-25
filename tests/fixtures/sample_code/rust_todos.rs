// TODO: Implement the main function
fn main() {
    // FIXME: This is broken
    let x = 42;
    
    /* HACK: Temporary workaround
     * until we fix the underlying issue
     */
    println!("Hello");
    
    // NOTE: This is important
    // BUG: Off by one error here
    // OPTIMIZE: Could be faster
    // DEPRECATED: Use new_function instead
    // SECURITY: Validate input
    // REVIEW: Check this logic
    // REFACTOR: Simplify this code
}

// Regular comment without keywords
// This TODO: is in the middle of text
// todolist: should not match (no word boundary)

fn example_function() {
    // TODO: Add error handling
    let result = risky_operation();
    
    // FIXME: Memory leak potential
    let data = allocate_data();
    
    // HACK: Workaround for compiler bug #1234
    unsafe {
        // SECURITY: This is unsafe code, review carefully
        transmute_memory(data);
    }
    
    // NOTE: Performance critical section
    for i in 0..1000 {
        // OPTIMIZE: Can we vectorize this?
        process_item(i);
    }
}

// DEPRECATED: Use new_api() instead
fn old_api() {
    // BUG: Race condition possible
    shared_state.modify();
}

/* Multi-line comment with TODO items
 * TODO: Refactor this entire module
 * FIXME: Handle edge cases
 * HACK: Quick fix for release
 */