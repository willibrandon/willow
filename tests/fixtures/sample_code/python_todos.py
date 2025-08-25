# TODO: Add error handling
def process_data(data):
    # FIXME: Handle None values
    if data is None:
        return
    
    # HACK: Quick fix for Python 3.9
    result = str(data)
    
    """
    TODO: Add documentation
    FIXME: Update for new API
    NOTE: This is a docstring with TODOs
    """
    
    # NOTE: 中文注释 TODO: 支持Unicode
    # SECURITY: Validate user input here
    if not validate_input(data):
        raise ValueError("Invalid input")
    
    # OPTIMIZE: This could be vectorized
    for item in data:
        # BUG: Doesn't handle nested structures
        process_item(item)
    
    return result

class DataProcessor:
    """
    DEPRECATED: Use DataProcessorV2 instead
    This class has known issues
    """
    
    def __init__(self):
        # REVIEW: Check if this initialization is correct
        self.state = {}
    
    def legacy_method(self):
        # TODO: Remove this method in v2.0
        pass

# Multi-line string with TODO
config = """
TODO: Move this to config file
FIXME: Add validation
{
    "setting": "value"
}
"""

def unicode_test():
    # TODO: 修复这个问题 🔧
    # FIXME: Ñoño está roto
    # HACK: Временное решение
    # NOTE: 日本語のコメント
    pass

# Edge cases
# todolist: should not match
# MY_TODO: should not match  
# TODO_ITEM: should not match