-- @file macos.lua.
-- @brief Defines all Solutions MacOS Dependencies.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get MacOS Libraries.
--
-- @param[in] includes Solution Includes.
--
-- @return Returns MacOS Libraries.
module.GetLibraries = function(includes)

    local library_dir                 = {
        ["VulkanSDK"]                 = includes.VulkanSDK .. "/../lib",                                              -- Library Directries: VulkanSDK Folder
    }

    local libraries                   = {
        ["VulkanSDK"]                 = library_dir.VulkanSDK .. "/libvulkan.so",                                     -- Library Directries: VulkanSDK
        ["shaderc"]                   = library_dir.VulkanSDK .. "/libshaderc.a",                                     -- Library Directries: shaderc
        ["shaderc_util"]              = library_dir.VulkanSDK .. "/libshaderc_util.a",                                -- Library Directries: shaderc_util
    }

    return libraries

end

return module