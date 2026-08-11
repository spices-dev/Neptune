-- @file Glad.lua.
-- @brief Defines Glad Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("Glad")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() ~= "emscripten" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/Glad/include",                                            -- Include: Glad
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {}

    -- Project
    module.project = solution_root .. "/Neptune/vendor/Glad"

end

return module