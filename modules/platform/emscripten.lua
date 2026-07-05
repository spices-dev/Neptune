-- @file emscripten.lua.
-- @brief Defines all Solutions Emscripten LinkOptions.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get Emscripten Executable LinkOptions.
--
-- @return Returns Emscripten Executable LinkOptions.
module.GetExecutableLinkOptions = function()

    local linkoptions = {
        "--use-port=%{vendor.includes.emscripten_glfw}/port/emscripten-glfw3.py",     -- Dependency: emscripten-glfw
        "--use-port=%{vendor.includes.emdawnwebgpu}/../../emdawnwebgpu.port.py",      -- Dependency: WebGPU
        "-s USE_WEBGL2=1",                                                            -- Dependency: WebGL
      --"-s USE_WEBGPU=1",                                                            -- This flag is deprecated(use emdawnwebgpu instead of official)
        "--closure=1",                                                                -- Reduce code size
        "-s DISABLE_EXCEPTION_CATCHING",                                              -- Disable Exception catch
        "-s ALLOW_MEMORY_GROWTH",                                                     -- Allow Memory growth
        "-s WASM_BIGINT",                                                             -- Enable BigInt in JS
        "-s WASM=1",                                                                  -- Output wasm
        "-s STACK_SIZE=4194304",                                                      -- Expand stack size to 4M
        "-s TOTAL_MEMORY=64MB",                                                       -- Wasm total memory to 64M
        "-s PROXY_TO_PTHREAD",                                                        -- Run in pthread(not main thread)
        "-s ASYNCIFY=1",                                                              -- Async between Wasm and Js
        "-s PTHREAD_POOL_SIZE=12",                                                    -- Js thread size 12
        "-pthread",                                                                   -- Enable pthread(required in both link and compile)
        "-s USE_PTHREADS=1",                                                          -- Use pthread
        "-s EXIT_RUNTIME=1",                                                          -- Allow return in runtime
        "-s SHARED_MEMORY",                                                           -- Shared memory
        "-s OFFSCREENCANVAS_SUPPORT",                                                 -- Transform canvas to pthread
        "-s OFFSCREENCANVASES_TO_PTHREAD='nepnep'",                                   -- Agent canvas to pthread
        "-o %{cfg.targetdir}/%{prj.name}.js"                                          -- Generate js file
    }

    return linkoptions

end

-- @brief Get Emscripten Executable Links.
--
-- @return Returns Emscripten Executable Links.
module.GetExecutableLinks = function()

    local links = {
    }

    return links

end

return module