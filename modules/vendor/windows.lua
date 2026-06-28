-- @file windows.lua.
-- @brief Defines all Solutions Windows Dependencies.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get Windows Libraries.
--
-- @param[in] includes Solution Includes.
--
-- @return Returns Windows Libraries.
module.GetLibraries = function(includes)

    local library_dir                 = {
        ["VulkanSDK"]                 = includes.VulkanSDK .. "/../Lib",                                              -- Library Directries: VulkanSDK Folder
        ["WinPixEventRuntime"]        = includes.WinPixEventRuntime .. "/../bin/x64",                                 -- Library Directries: WinPixEventRuntime Folder
    }

    local libraries                   = {
        ["VulkanSDK"]                 = library_dir.VulkanSDK .. "/vulkan-1.lib",                                     -- Library Directries: VulkanSDK
        ["dxgi"]                      = "dxgi.lib",                                                                   -- Library Directries: dxgi
        ["d3d11"]                     = "d3d11.lib",                                                                  -- Library Directries: d3d11
        ["d3d12"]                     = "d3d12.lib",                                                                  -- Library Directries: d3d12
        ["WinPixEventRuntime"]        = library_dir.WinPixEventRuntime .. "/WinPixEventRuntime.lib",                  -- Library Directries: WinPixEventRuntime

        ["shaderc_debug"]             = library_dir.VulkanSDK .. "/shaderc_sharedd.lib",                              -- Library Directries: shaderc_debug
        ["shaderc_util_debug"]        = library_dir.VulkanSDK .. "/shaderc_utild.lib",                                -- Library Directries: shaderc_util_debug

        ["shaderc_release"]           = library_dir.VulkanSDK .. "/shaderc_shared.lib",                               -- Library Directries: shaderc_release
        ["shaderc_util_release"]      = library_dir.VulkanSDK .. "/shaderc_util.lib",                                 -- Library Directries: shaderc_util_release
    }

    return libraries

end

return module