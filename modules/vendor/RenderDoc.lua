-- @file RenderDoc.lua.
-- @brief Defines RenderDoc Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("RenderDoc")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    solution_root .. "/Neptune/vendor/RenderDoc/include",                                           -- Include: RenderDoc
}

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

if os.target() == "macosx" then

    -- Dynamic Library Dependencies
    module.dynamic_libraries = {
        solution_root .. "/Neptune/vendor/RenderDoc/bin/linux/librenderdoc.so",                     -- Library: RenderDoc
    }

end

return module