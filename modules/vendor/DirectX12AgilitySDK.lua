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
    module.libraries = {}

end

return module