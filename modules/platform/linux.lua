-- @file linux.lua.
-- @brief Defines all Solutions linux LinkOptions.
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

-- @brief Get Executable LinkOptions.
--
-- @return Returns Executable LinkOptions.
module.GetExecutableLinkOptions = function()

    local linkoptions = {}

    return linkoptions

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

    local graphics = module.GetGraphicsFeatures()

    if table.contains(graphics, "NP_GRAPHICS_OPENGL") then
        table.insert(list, "NP_RHICAPTURER_RENDERDOC")              -- RHICapturer: RenderDoc
    end

    return list

end

-- @brief Get Window Feature Lists.
-- 
-- @return Returns Window Feature Lists.
module.GetWindowFeatures = function()

    local list = {}

    table.insert(list, "NP_WINDOW_GLFW")               -- Window: GLFW.
    table.insert(list, "GLFW_INCLUDE_NONE")            -- Exclude <GL/gl.h>, we provide glad.

    return list

end

-- @brief Get Executable Links.
--
-- @return Returns Executable Links.
module.GetExecutableLinks = function()

    local links = {}

    return links

end

return module