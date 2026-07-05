-- @file windows.lua.
-- @brief Defines all Solutions windows LinkOptions.
-- @author Spices.

-- Define module
local module = {}

-- @brief Is item in table.
--
-- @param[in] t table
-- @param[in] value search value
--
-- @return Returns true if contains.
function table.contains(t, value)

    for _, v in ipairs(t) do
        if v == value then return true end
    end

    return false

end

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

    local windows  = platform.GetWindowFeatures()
    local profiler = platform.GetProfilerFeatures()

    local links = {}

    if table.contains(windows, "NP_WINDOW_GLFW") then
        table.insert(links, "gdi32")                                 -- Dependency: Windows Graphics Device Interface
        table.insert(links, "user32")                                -- Dependency: Windows GDI UI
        table.insert(links, "shell32")                               -- Dependency: Windows Shell API 
    end

    if table.contains(profiler, "NP_PROFILE_TRACY") then
        table.insert(links, "ws2_32")                                -- Dependency: Windows Socket
        table.insert(links, "dbghelp")                               -- Dependency: DbgHelp
    end

    if _OPTIONS["cc"] == "gcc" then
        table.insert(links, "mingw32")                               -- Dependency: MinGW 32-bit Runtime
        table.insert(links, "mingwex")                               -- Dependency: MinGW Extended Runtime Library
        table.insert(links, "ucrt")                                  -- Dependency: Universal C Runtime
    end
    
    return links

end

return module