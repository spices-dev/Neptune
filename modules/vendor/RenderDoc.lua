-- @file RenderDoc.lua.
-- @brief Defines RenderDoc Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/RenderDoc/include",                                           -- Include: RenderDoc
}

-- Library Directories
module.library_dirs = {}

-- Library Dependencies
module.libraries = {}

if os.target() == "windows" then

    -- Dynamic Library Dependencies
    module.dynamic_libraries = {
        solution_root .. "/Neptune/vendor/RenderDoc/bin/x64/renderdoc.dll",                         -- Library: RenderDoc
    }

end

if os.target() == "linux" then

    -- Dynamic Library Dependencies
    module.dynamic_libraries = {
        solution_root .. "/Neptune/vendor/RenderDoc/bin/linux/librenderdoc.so",                     -- Library: RenderDoc
    }

end

return module