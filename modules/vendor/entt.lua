-- @file entt.lua.
-- @brief Defines entt Third Party.
-- @author Spices.

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("entt")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/entt/include",                                            -- Include: entt
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module