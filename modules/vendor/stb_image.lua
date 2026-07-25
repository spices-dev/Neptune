-- @file stb_image.lua.
-- @brief Defines stb_image Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/stb_image",                                               -- Include: stb_image
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module