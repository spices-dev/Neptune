-- @file ImPlot.lua.
-- @brief Defines ImPlot Third Party.
-- @author Spices.

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("ImPlot")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/implot",                                                  -- Include: ImPlot
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

-- Project
module.project = solution_root .. "/Neptune/vendor/implot"

return module