-- @file spdlog.lua.
-- @brief Defines spdlog Third Party.
-- @author Spices.

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("spdlog")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/spdlog/include",                                          -- Include: spdlog
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

return module