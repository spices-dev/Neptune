-- @file vma.lua.
-- @brief Defines vma Third Party.
-- @author Spices.

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("vma")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/vma/include",                                             -- Include: vma
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module