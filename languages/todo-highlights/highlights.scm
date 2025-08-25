; TODO patterns
(todo_item 
  keyword: (keyword) @comment.todo.keyword
  message: (message)? @comment.todo.message)

; FIXME patterns  
(fixme_item
  keyword: (keyword) @comment.fixme.keyword
  message: (message)? @comment.fixme.message)

; HACK patterns
(hack_item
  keyword: (keyword) @comment.hack.keyword
  message: (message)? @comment.hack.message)

; NOTE patterns
(note_item
  keyword: (keyword) @comment.note.keyword
  message: (message)? @comment.note.message)

; BUG patterns
(bug_item
  keyword: (keyword) @comment.bug.keyword
  message: (message)? @comment.bug.message)

; OPTIMIZE patterns
(optimize_item
  keyword: (keyword) @comment.optimize.keyword
  message: (message)? @comment.optimize.message)

; DEPRECATED patterns
(deprecated_item
  keyword: (keyword) @comment.deprecated.keyword
  message: (message)? @comment.deprecated.message)

; SECURITY patterns
(security_item
  keyword: (keyword) @comment.security.keyword
  message: (message)? @comment.security.message)

; REVIEW patterns
(review_item
  keyword: (keyword) @comment.review.keyword
  message: (message)? @comment.review.message)

; REFACTOR patterns
(refactor_item
  keyword: (keyword) @comment.refactor.keyword
  message: (message)? @comment.refactor.message)