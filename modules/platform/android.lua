-- @file android.lua.
-- @brief Defines all Solutions Android LinkOptions.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get Compute Feature Lists.
--
-- @return Returns Compute Feature Lists.
module.GetComputeFeatures = function()

    local list = {}

    return list

end

-- @brief Get Graphics Feature Lists.
-- 
-- @return Returns Graphics Feature Lists.
module.GetGraphicsFeatures = function()

    local list = {
        "NP_GRAPHICS_OPENGL",                              -- Graphics: OpenGL
        "NP_GRAPHICS_VULKAN",                              -- Graphics: Vulkan
        "VK_ENABLE_BETA_EXTENSIONS",                       -- Enable Vulkan Beta Extensions
    }

    return list

end

-- @brief Get Debugger Feature Lists.
-- 
-- @return Returns Debugger Feature Lists.
module.GetDebuggerFeatures = function()

    local list = {}

    table.insert(list, "NP_PROFILER_TRACY")                -- Profiler: tracy
    table.insert(list, "TRACY_ENABLE")                     -- tracy Feature Enable.
    table.insert(list, "TRACY_ON_DEMAND")                  -- Used if want profile on demand.
    table.insert(list, "TRACY_FIBERS")                     -- Enable fiber thread.
    table.insert(list, "TRACY_IMPORT")                     -- Multi dll.

    return list

end

-- @brief Get Window Feature Lists.
-- 
-- @return Returns Window Feature Lists.
module.GetWindowFeatures = function()

    local list = {}

    table.insert(list, "NP_WINDOW_ANDROIDNATIVE")      -- Window: Android Native.

    return list

end

-- @brief Get Executable LinkOptions.
--
-- @return Returns Executable LinkOptions.
module.GetExecutableLinkOptions = function()

    local windows  = module.GetWindowFeatures()
    local graphics = module.GetGraphicsFeatures()

    local linkoptions = {}

    table.insert(linkoptions, "-llog")                                   -- Dependency: log

    if table.contains(windows, "NP_WINDOW_ANDROIDNATIVE") then
        table.insert(linkoptions, "-landroid")                           -- Dependency: android
    end

    if table.contains(graphics, "NP_GRAPHICS_OPENGL") then
        table.insert(linkoptions, "-lGLESv2")                            -- Dependency: GLESv2
        table.insert(linkoptions, "-lEGL")                               -- Dependency: EGL
    end
    
    if table.contains(graphics, "NP_GRAPHICS_VULKAN") then
        table.insert(linkoptions, "-lvulkan")                            -- Dependency: vulkan
    end

    return linkoptions

end

-- @brief Get Executable Links.
--
-- @return Returns Executable Links.
module.GetExecutableLinks = function()

    local links = {}

    return links

end

return module