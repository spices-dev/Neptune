-- @file WinPixEventRuntime.lua.
-- @brief Defines WinPixEventRuntime Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "windows" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/PixEvents/include",                                       -- Include: WinPixEventRuntime
    }

    -- Library Directories
    module.library_dirs = {
        solution_root .. "/Neptune/vendor/PixEvents/lib/x64",                                       -- Library Directries: WinPixEventRuntime Folder
    }

    -- Library Dependencies
    module.libraries = {
        "dxgi",                                                                                     -- Library: dxgi
        "d3d11",                                                                                    -- Library: d3d11
        "d3dcompiler",                                                                              -- Library: d3dcompiler
        "d3d12",                                                                                    -- Library: d3d12
        "WinPixEventRuntime",                                                                       -- Library: WinPixEventRuntime
    }

    -- Dynamic Library Dependencies
    module.dynamic_libraries = {
        solution_root .. "/Neptune/vendor/PixEvents/lib/x64/WinPixEventRuntime.dll",                -- Library: WinPixEventRuntime
    }

end

return module