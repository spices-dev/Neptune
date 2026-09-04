-- @file rapidyaml.lua.
-- @brief Defines rapidyaml Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("rapidyaml")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/rapidyaml",                                               -- Include: rapidyaml
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module