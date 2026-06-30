-- @file platform.lua.
-- @brief Defines all Solutions Platform behavies.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get Compute Feature Lists.
--
-- @return Returns Compute Feature Lists.
module.GetComputeFeatures = function()

    local list = {}

    local isClang = (_OPTIONS["cc"] == "clang") or (_OPTIONS["cc"] == "clang++")

    if os.target() == "windows" and isClang then
        table.insert(list, "NP_COMPUTE_SYCL")              -- Compute: SYCL
    end

    return list

end

-- @brief Get Graphics Feature Lists.
-- 
-- @return Returns Graphics Feature Lists.
module.GetGraphicsFeatures = function()

    local list = {}

    if os.target() == "emscripten" then
        table.insert(list, "NP_GRAPHICS_WEBGL")            -- Graphics: WebGL
        table.insert(list, "NP_GRAPHICS_WEBGPU")           -- Graphics: WebGPU
    end

    if os.target() ~= "emscripten" then
        table.insert(list, "NP_GRAPHICS_OPENGL")           -- Graphics: OpenGL
        table.insert(list, "NP_GRAPHICS_VULKAN")           -- Graphics: Vulkan
    end

    if os.target() == "windows" then
        table.insert(list, "NP_GRAPHICS_DIRECT3D11")       -- Graphics: Direct3D11
        table.insert(list, "NP_GRAPHICS_DIRECT3D12")       -- Graphics: Direct3D12
    end

    if os.target() == "macosx" then
        table.insert(list, "NP_GRAPHICS_METAL")            -- Graphics: Metal
    end

    return list

end

-- @brief Get Profiler Feature Lists.
-- 
-- @return Returns Profiler Feature Lists.
module.GetProfilerFeatures = function()

    local list = {}

    table.insert(list, "NP_PROFILE_TRACY")                 -- Profiler: tracy
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

    if os.target() ~= "emscripten" then
        table.insert(list, "NP_WINDOW_GLFW")               -- Window: GLFW.
        table.insert(list, "GLFW_INCLUDE_NONE")            -- Exclude <GL/gl.h>, we provide glad.
    else
        table.insert(list, "NP_WINDOW_EMSCRIPTENGLFW")     -- Window: emscripten_glfw.
        table.insert(list, "GLFW_INCLUDE_NONE")            -- Exclude <GL/gl.h>, we provide glad.
    end

    return list

end

-- @brief Get Sub Platform Executable LinkOptions.
-- 
-- @return Returns Sub Platform Executable LinkOptions.
module.GetExecutableLinkOptions = function()

    local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

    local sub_platform  = {
        windows         = current_dir .. "null.lua",
        linux           = current_dir .. "null.lua",
        macosx          = current_dir .. "null.lua",
        emscripten      = current_dir .. "emscripten.lua",
    }

    return loadfile(sub_platform[os.target()])().GetExecutableLinkOptions() or {}

end

-- @brief module Initialize.
module.Initialize = function()

    -- Platform: Windows
    filter "system:windows"

        -- Architecture x64
        architecture "x64"

        -- Use Lastest WindowSDK
		systemversion "latest"

        -- Windows Specific Solution Macro Definitions.
        defines
		{
			-- Use winsock2.h instead of winsock.h.
			"WIN32_LEAN_AND_MEAN",

			-- Use M_PI Macro.
			"_USE_MATH_DEFINES",

			-- NO MIN MAX Macro
			"NOMINMAX",
			
			-- Define Platform: Windows.
			"NP_PLATFORM_WINDOWS",
		}

    -- Platform: Linux
	filter "system:linux"

        -- Use Lastest SystemVersion
		systemversion "latest"

        -- Windows Specific Solution Macro Definitions.
		defines
		{
			-- Define Platform: Linux.
			"NP_PLATFORM_LINUX"
		}

    -- Platform: MacOS
	filter "system:macosx"

        -- Use Lastest SystemVersion
		systemversion "latest"

        -- Windows Specific Solution Macro Definitions.
		defines
		{
			-- Define Platform: MacOS.
			"NP_PLATFORM_MACOS"
		}

    -- Platform: Emscripten
	filter "system:emscripten"

        -- Architecture wasm64
        architecture "wasm64"

        -- Use Lastest SystemVersion
		systemversion "latest"

        -- Emscripten Specific Solution Macro Definitions.
		defines
		{
			-- Define Platform: Emscripten.
			"NP_PLATFORM_EMSCRIPTEN"
		}

    -- Configuration: Debug
	filter "configurations:Debug"

		-- Debug Specific Solution Macro Definitions.
		defines 
		{
			"NEPTUNE_DEBUG",  -- Debug Symbol.
		}

        runtime "Debug"
		symbols "On"

    -- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines 
		{
			"NEPTUNE_RELEASE",  -- Release Symbol.
		}

		runtime "Release"
		optimize "On"

end

return module