; Based on Helix's approach
(tag
 (name) @text
 (user)? @constant)

; Info level tags
((tag (name) @comment.todo)
 (#any-of? @comment.todo "TODO" "todo" "Todo"))

((tag (name) @comment.note)
 (#any-of? @comment.note "NOTE" "note" "Note" "INFO" "info"))

; Warning level tags  
((tag (name) @comment.fixme)
 (#any-of? @comment.fixme "FIXME" "fixme" "FixMe" "FIX" "fix"))

((tag (name) @comment.hack)
 (#any-of? @comment.hack "HACK" "hack" "Hack" "WARN" "WARNING"))

; Error level tags
((tag (name) @comment.bug)
 (#any-of? @comment.bug "BUG" "bug" "Bug" "ERROR" "XXX"))

; Special patterns
((tag (name) @comment.deprecated)
 (#any-of? @comment.deprecated "DEPRECATED" "deprecated" "OBSOLETE"))

((tag (name) @comment.security)
 (#any-of? @comment.security "SECURITY" "SAFETY" "SEC"))

((tag (name) @comment.optimize)
 (#any-of? @comment.optimize "OPTIMIZE" "OPTIMISE" "optimize" "optimise" "PERF" "PERFORMANCE"))

((tag (name) @comment.review)
 (#any-of? @comment.review "REVIEW" "review" "Review" "CHECK"))

((tag (name) @comment.refactor)
 (#any-of? @comment.refactor "REFACTOR" "refactor" "Refactor" "CLEANUP" "cleanup"))

; Fallback for plain text patterns (without colon)
("text" @comment.todo
 (#match? @comment.todo "\\b(TODO|todo|Todo)\\b"))

("text" @comment.fixme
 (#match? @comment.fixme "\\b(FIXME|fixme|FixMe)\\b"))

("text" @comment.hack
 (#match? @comment.hack "\\b(HACK|hack|Hack)\\b"))