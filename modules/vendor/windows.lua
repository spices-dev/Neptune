-- @file windows.lua.
-- @brief Defines all Solutions Windows Dependencies.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get Windows LibraryDirs.
--
-- @param[in] includes Solution Includes.
--
-- @return Returns Windows LibraryDirs.
module.GetLibraryDirs = function(includes)

    local library_dir                 = {
        ["VulkanSDK"]                 = includes.VulkanSDK .. "/../Lib",                                              -- Library Directries: VulkanSDK Folder
        ["WinPixEventRuntime"]        = includes.WinPixEventRuntime .. "/../bin/x64",                                 -- Library Directries: WinPixEventRuntime Folder
    }

    return library_dir

end

-- @brief Get Windows Libraries.
--
-- @return Returns Windows Libraries.
module.GetLibraries = function()

    local libraries                   = {
        ["vulkan"]                    = "vulkan-1",                                                                   -- Library: vulkan
        ["dxgi"]                      = "dxgi",                                                                       -- Library: dxgi
        ["d3d11"]                     = "d3d11",                                                                      -- Library: d3d11
        ["d3dcompiler"]               = "d3dcompiler",                                                                -- Library: d3dcompiler
        ["d3d12"]                     = "d3d12",                                                                      -- Library: d3d12
        ["WinPixEventRuntime"]        = "WinPixEventRuntime",                                                         -- Library: WinPixEventRuntime

        ["shaderc_debug"]             = "shaderc_sharedd",                                                            -- Library: shaderc_debug
        ["shaderc_util_debug"]        = "shaderc_utild",                                                              -- Library: shaderc_util_debug

        ["shaderc_release"]           = "shaderc_shared",                                                             -- Library: shaderc_release
        ["shaderc_util_release"]      = "shaderc_util",                                                               -- Library: shaderc_util_release
    }

    return libraries

end

return module