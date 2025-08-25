-- TODO: Add type signatures
module Example where

-- FIXME: Lazy evaluation issues
data Example = Example String

-- HACK: GHC extension workaround
-- NOTE: Uses monads
-- BUG: Space leak
-- OPTIMIZE: Use strict evaluation
-- DEPRECATED: Use newExample
-- SECURITY: Validate IO operations
-- REVIEW: Monad transformer stack
-- REFACTOR: Extract to typeclass

process :: Example -> IO ()
process ex = do
  -- TODO: Add error handling
  return ()