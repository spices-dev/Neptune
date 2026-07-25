-- @file Glad.lua.
-- @brief Defines Glad Third Party.
-- @author Spices.

-- Define module
local module = {}

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