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

-- @brief Get Compute Feature Lists.
--
-- @return Returns Compute Feature Lists.
module.GetComputeFeatures = function()

    local list = {}

    local isClang = (_OPTIONS["cc"] == "clang") or (_OPTIONS["cc"] == "clang++")

    if isClang then
      --table.insert(list, "NP_COMPUTE_SYCL")              -- Compute: SYCL
    end

    return list

end

-- @brief Get Graphics Feature Lists.
-- 
-- @return Returns Graphics Feature Lists.
module.GetGraphicsFeatures = function()

    local list = {
        "NP_GRAPHICS_OPENGL",                              -- Graphics: OpenGL
        "NP_GRAPHICS_VULKAN",                              -- Graphics: Vulkan
        "NP_GRAPHICS_DIRECT3D11",                          -- Graphics: Direct3D11
        "NP_GRAPHICS_DIRECT3D12",                          -- Graphics: Direct3D12
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

-- @brief Get Executable LinkOptions.
--
-- @return Returns Executable LinkOptions.
module.GetExecutableLinkOptions = function()

    local linkoptions = {}

    return linkoptions

end

-- @brief Get Executable Links.
--
-- @return Returns Executable Links.
module.GetExecutableLinks = function()

    local windows  = module.GetWindowFeatures()
    local debugger = module.GetDebuggerFeatures()

    local links = {}

    if table.contains(windows, "NP_WINDOW_GLFW") then
        table.insert(links, "gdi32")                                 -- Dependency: Windows Graphics Device Interface
        table.insert(links, "user32")                                -- Dependency: Windows GDI UI
        table.insert(links, "shell32")                               -- Dependency: Windows Shell API 
    end

    if table.contains(debugger, "NP_PROFILER_TRACY") then
        table.insert(links, "ws2_32")                                -- Dependency: Windows Socket
        table.insert(links, "dbghelp")                               -- Dependency: DbgHelp
    end

    -- Noto: needs to be the last links.
    if _OPTIONS["cc"] == "gcc" then
        table.insert(links, "mingw32")                               -- Dependency: MinGW 32-bit Runtime
        table.insert(links, "mingwex")                               -- Dependency: MinGW Extended Runtime Library
        table.insert(links, "ucrt")                                  -- Dependency: Universal C Runtime
    end
    
    return links

end

return module