-- @file DirectX-Headers.lua.
-- @brief Defines DirectX-Headers Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("DirectX-Headers")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "windows" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/DirectX-Headers/include",                                 -- Include: DirectX-Headers
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {}

end

return module