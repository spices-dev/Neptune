-- @file miniz.lua.
-- @brief Defines miniz Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("miniz")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/miniz",                                        -- Include: miniz
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

-- Project
module.project = solution_root .. "/Neptune/vendor/miniz"

return module