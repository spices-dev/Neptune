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
        table.insert(list, "NP_COMPUTE_SYCL")
    end

    return list

end

-- @brief Get Graphics Feature Lists.
-- 
-- @return Returns Graphics Feature Lists.
module.GetGraphicsFeatures = function()

    local list = {}

    if os.target() == "emscripten" then
        table.insert(list, "NP_GRAPHICS_WEBGL")
        table.insert(list, "NP_GRAPHICS_WEBGPU")
    end

    if os.target() ~= "emscripten" then
        table.insert(list, "NP_GRAPHICS_OPENGL")
        table.insert(list, "NP_GRAPHICS_VULKAN")
    end

    if os.target() == "windows" then
        table.insert(list, "NP_GRAPHICS_DIRECT3D11")
        table.insert(list, "NP_GRAPHICS_DIRECT3D12")
    end

    if os.target() == "macosx" then
        table.insert(list, "NP_GRAPHICS_METAL")
    end

    return list

end

-- @brief Get Profile Feature Lists.
-- 
-- @return Returns Profile Feature Lists.
module.GetProfileFeatures = function()

    local list = {}

    if os.target() ~= "emscripten" then
        table.insert(list, "NP_PROFILE_TRACY")
        table.insert(list, "TRACY_ENABLE")                -- tracy Feature Enable.
        table.insert(list, "TRACY_ON_DEMAND")             -- Used if want profile on demand.
        table.insert(list, "TRACY_FIBERS")                -- Enable fiber thread.
        table.insert(list, "TRACY_IMPORT")                -- Multi dll.
    end

    return list

end

-- @brief module Initialize.
module.Initialize = function()

    -- Platform: Windows
    filter "system:windows"

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
			"NP_PLATFORM_WINDOWS"
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