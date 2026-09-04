-- @file yaml-cpp.lua.
-- @brief Defines yaml-cpp Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("yaml-cpp")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/yaml-cpp/include",                                        -- Include: yaml-cpp
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

-- Project
module.project = solution_root .. "/Neptune/vendor/yaml-cpp"

return module