-- @file Vulkan.lua.
-- @brief Defines Vulkan Third Party.
-- @author Spices.

-- Default Version
local default_version = "1.4.357.0"

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
        macosx  = os.getenv("HOME") .. "/VulkanSDK/" .. default_version .. "/macos/include",
    }

    return default_paths[os.target()] or ""

end

-- Current Folder Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Define module
local module = loadfile(current_dir .. "vender_base.lua")().NewModule("Vulkan")

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Includes
module.includes = {
    GetVulkanSDKPath(),                                                               -- Include: VulkanSDK
}

return module