-- @file yaml-cpp.lua.
-- @brief Defines yaml-cpp Third Party.
-- @author Spices.

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