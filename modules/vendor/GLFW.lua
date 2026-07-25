-- @file GLFW.lua.
-- @brief Defines GLFW Third Party.
-- @author Spices.

-- Define module
local module = {}

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