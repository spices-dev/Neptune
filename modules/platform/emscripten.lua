-- @file emscripten.lua.
-- @brief Defines all Solutions Emscripten LinkOptions.
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
        "NP_GRAPHICS_WEBGL",                               -- Graphics: WebGL
        "NP_GRAPHICS_WEBGPU",                              -- Graphics: WebGPU
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

    table.insert(list, "NP_WINDOW_EMSCRIPTENGLFW")     -- Window: emscripten_glfw.
    table.insert(list, "GLFW_INCLUDE_NONE")            -- Exclude <GL/gl.h>, we provide glad.

    return list

end

-- @brief Get Executable LinkOptions.
--
-- @return Returns Executable LinkOptions.
module.GetExecutableLinkOptions = function()

    local linkoptions = {
        "--use-port=%{vendor.emscripten_glfw.includes[1]}/../port/emscripten-glfw3.py",     -- Dependency: emscripten-glfw
        "--use-port=%{vendor.emdawnwebgpu.includes[1]}/../../emdawnwebgpu.port.py",         -- Dependency: WebGPU
        "-s USE_WEBGL2=1",                                                                  -- Dependency: WebGL
      --"-s USE_WEBGPU=1",                                                                  -- This flag is deprecated(use emdawnwebgpu instead of official)
        "--closure=1",                                                                      -- Reduce code size
        "-s DISABLE_EXCEPTION_CATCHING",                                                    -- Disable Exception catch
        "-s ALLOW_MEMORY_GROWTH",                                                           -- Allow Memory growth
        "-s WASM_BIGINT",                                                                   -- Enable BigInt in JS
        "-s WASM=1",                                                                        -- Output wasm
        "-s STACK_SIZE=4194304",                                                            -- Expand stack size to 4M
        "-s TOTAL_MEMORY=64MB",                                                             -- Wasm total memory to 64M
        "-s PROXY_TO_PTHREAD",                                                              -- Run in pthread(not main thread)
        "-s ASYNCIFY=1",                                                                    -- Async between Wasm and Js
        "-s PTHREAD_POOL_SIZE=12",                                                          -- Js thread size 12
        "-pthread",                                                                         -- Enable pthread(required in both link and compile)
        "-s USE_PTHREADS=1",                                                                -- Use pthread
        "-s EXIT_RUNTIME=1",                                                                -- Allow return in runtime
        "-s SHARED_MEMORY",                                                                 -- Shared memory
        "-s OFFSCREENCANVAS_SUPPORT",                                                       -- Transform canvas to pthread
        "-s OFFSCREENCANVASES_TO_PTHREAD='nepnep'",                                         -- Agent canvas to pthread
        "-o %{cfg.targetdir}/%{prj.name}.js"                                                -- Generate js file
    }

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