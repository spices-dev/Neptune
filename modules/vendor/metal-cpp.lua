-- @file metal-cpp.lua.
-- @brief Defines metal-cpp Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "macosx" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/metal-cpp",                                        -- Include: metal-cpp
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {}

end

return module