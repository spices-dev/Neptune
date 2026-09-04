-- @file Neptune.lua.
-- @brief Defines Neptune Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("Neptune")

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