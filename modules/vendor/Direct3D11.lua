-- @file Direct3D11.lua.
-- @brief Defines Direct3D11 Third Party.
-- @author Spices.

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("Direct3D11")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "windows" then

    -- Includes
    module.includes = {}

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {
        "dxgi",                                                                                     -- Library: dxgi
        "d3d11",                                                                                    -- Library: d3d11
        "d3dcompiler",                                                                              -- Library: d3dcompiler
    }

end

return module