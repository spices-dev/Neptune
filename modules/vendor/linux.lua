-- @file linux.lua.
-- @brief Defines all Solutions Linux Dependencies.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get Linux LibraryDirs.
--
-- @param[in] includes Solution Includes.
--
-- @return Returns Linux LibraryDirs.
module.GetLibraryDirs = function(includes)

    local library_dir                 = {
        ["VulkanSDK"]                 = includes.VulkanSDK .. "/../lib",                                              -- Library Directries: VulkanSDK Folder
    }

    return library_dir

end

-- @brief Get Linux Libraries.
--
-- @return Returns Linux Libraries.
module.GetLibraries = function()

    local libraries                   = {
        ["vulkan"]                    = "vulkan",                                                                     -- Library: vulkan
    }

    return libraries

end

return module
