-- @file windows.lua.
-- @brief Defines all Solutions windows LinkOptions.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get Windows Executable LinkOptions.
--
-- @return Returns Windows Executable LinkOptions.
module.GetExecutableLinkOptions = function()

    local linkoptions = {
    }

    return linkoptions

end

-- @brief Get Windows Executable Links.
--
-- @return Returns Windows Executable Links.
module.GetExecutableLinks = function()

    local links = {
        "gdi32",                                                   -- Dependency: Windows Graphics Device Interface
        "shell32",                                                 -- Dependency: Windows Shell AP
    }

    return links

end

return module