-- @file Vulkan.lua.
-- @brief Defines Vulkan Third Party.
-- @author Spices.

-- Default Version
local default_version = "1.4.321.1"

-- @brief Get Vulkan SDK Path.
--
-- @return Returns Vulkan SDK Path.
local GetVulkanSDKPath = function()

    -- Search in Env first.
    local sdk_path = os.getenv("VULKAN_SDK") or ""
    sdk_path = sdk_path:gsub("\\", "/")

    local include_dir = (os.target() == "windows") and "Include" or "include"

    if sdk_path ~= "" then
        return sdk_path .. "/" .. include_dir
    end

    -- Default Vulkan Path.
    local default_paths = {
        windows = "C:/VulkanSDK/" .. default_version .. "/Include",
        linux   = os.getenv("HOME") .. "/VulkanSDK/" .. default_version .. "/x86_64/include",
        macosx  = ""
    }

    return default_paths[os.target()] or ""

end

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    GetVulkanSDKPath(),                                                               -- Include: VulkanSDK
}

if os.target() == "windows" then

    -- Library Directories
    module.library_dirs = {
        GetVulkanSDKPath() .. "/../Lib",                                              -- Library Directries: VulkanSDK Folder
    }

    -- Library Dependencies
    module.libraries = {
        "vulkan-1",                                                                   -- Library: vulkan
    }

end

if os.target() == "linux" then

    -- Library Directories
    module.library_dirs = {
        GetVulkanSDKPath() .. "/../lib",                                              -- Library Directries: VulkanSDK Folder
    }

    -- Library Dependencies
    module.libraries = {
        "vulkan",                                                                     -- Library: vulkan
    }

end

if os.target() == "macosx" then

    -- Library Directories
    module.library_dirs = {
        GetVulkanSDKPath() .. "/../lib",                                              -- Library Directries: VulkanSDK Folder
    }

    -- Library Dependencies
    module.libraries = {
        "vulkan",                                                                     -- Library: vulkan
    }

end

return module