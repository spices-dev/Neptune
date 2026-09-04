-- @file googletest.lua.
-- @brief Defines googletest Third Party.
-- @author Spices.

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("googletest")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/UnitTest/vendor/googletest/googletest/include",                          -- Include: googletest
    solution_root .. "/UnitTest/vendor/googletest/googlemock/include",                          -- Include: googlemock
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

-- Project
module.project = solution_root .. "/UnitTest/vendor/googletest"

return module