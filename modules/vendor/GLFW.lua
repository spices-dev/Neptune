-- @file GLFW.lua.
-- @brief Defines GLFW Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("GLFW")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() ~= "emscripten" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/GLFW/include",                                            -- Include: GLFW
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {}

    -- Project
    module.project = solution_root .. "/Neptune/vendor/GLFW"

end

return module