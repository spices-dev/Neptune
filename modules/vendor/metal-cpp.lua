-- @file metal-cpp.lua.
-- @brief Defines metal-cpp Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("metal-cpp")

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