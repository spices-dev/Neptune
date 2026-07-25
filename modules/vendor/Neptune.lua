-- @file Neptune.lua.
-- @brief Defines Neptune Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/src",                                -- Include: Neptune
    solution_root .. "/Neptune/assets/Shaders/src"                  -- Include: Neptune Shaders
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module