-- @file DirectX12AgilitySDK.lua.
-- @brief Defines DirectX12AgilitySDK Third Party.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

if os.target() == "windows" then

    -- Includes
    module.includes = {
        solution_root .. "/Neptune/vendor/Microsoft.Direct3D.D3D12/build/native/include",           -- Include: DirectX12AgilitySDK
    }

    -- Library Directories
    module.library_dirs = {}

    -- Library Dependencies
    module.libraries = {
        "dxgi",                                                                                     -- Library: dxgi
        "d3d12",                                                                                    -- Library: d3d12
        "d3dcompiler",                                                                              -- Library: d3dcompiler
    }

    -- Dynamic Library Dependencies
    module.dynamic_libraries = {
        solution_root .. "/Neptune/vendor/Microsoft.Direct3D.D3D12/build/native/bin/x64/D3D12Core.dll",         -- Library: D3D12Core
        solution_root .. "/Neptune/vendor/Microsoft.Direct3D.D3D12/build/native/bin/x64/d3d12SDKLayers.dll",    -- Library: d3d12SDKLayers
    }

end

return module