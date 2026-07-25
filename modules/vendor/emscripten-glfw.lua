-- @file emscripten-glfw.lua.
-- @brief Defines emscripten-glfw Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "emscripten" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/emscripten-glfw/include",                                   -- Include: emscripten-glfw
        solution_root .. "/Neptune/vendor/emscripten-glfw/external",                                  -- Include: emscripten-glfw
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {}

end

return module