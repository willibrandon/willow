// TODO: Convert to TypeScript
function processData(data) {
    // FIXME: Add type checking
    if (!data) return null;
    
    /* TODO: Refactor this mess
     * HACK: Works for now
     * NOTE: Performance critical
     * OPTIMIZE: Use better algorithm
     */
    
    // BUG: Doesn't handle arrays
    return data.toString();
}

class DataManager {
    constructor() {
        // SECURITY: Add authentication check
        this.authenticated = false;
        
        // DEPRECATED: Remove in next version
        this.legacyMode = true;
    }
    
    // TODO: Add JSDoc comments
    processItem(item) {
        // REVIEW: Is this the right approach?
        if (this.legacyMode) {
            // HACK: Legacy compatibility
            return this.legacyProcess(item);
        }
        
        // NOTE: New processing logic
        return this.modernProcess(item);
    }
    
    legacyProcess(item) {
        // FIXME: This has known bugs
        // BUG: Memory leak in large datasets
        return item.process();
    }
}

/* Multi-line comment with various TODOs
 * TODO: Add error boundaries
 * FIXME: Handle async operations
 * HACK: Temporary DOM manipulation
 * SECURITY: XSS vulnerability possible
 */

// Arrow function with TODO
const asyncHandler = async (data) => {
    // TODO: Add proper error handling
    try {
        // OPTIMIZE: Batch these operations
        const results = await Promise.all([
            fetchData(data.id),
            validateData(data),
            processData(data)
        ]);
        
        // REVIEW: Do we need all this data?
        return results;
    } catch (error) {
        // FIXME: Better error reporting
        console.error(error);
        throw error;
    }
};

// Template literals with TODOs
const template = `
    <!-- TODO: Add proper HTML structure -->
    <div class="container">
        <!-- FIXME: Accessibility issues -->
        <button onclick="handleClick()">Click me</button>
        <!-- NOTE: This needs styling -->
    </div>
`;

// Regular expressions
const regex = /TODO:\s*(.*)/g; // This TODO: should not be highlighted in string

/* Regular block comment */
// todoapp: should not match
// MY_TODO: should not match