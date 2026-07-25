-- @file glm.lua.
-- @brief Defines glm Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/glm",                                                     -- Include: glm
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module