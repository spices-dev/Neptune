-- @file platform.lua.
-- @brief Defines all Solutions Platform behavies.
-- @author Spices.

-- Define module
local module = {}

-- Current Directory
local current_dir = debug.getinfo(1, "S").source:sub(2):match("(.*/)") or "./"

-- Sub Platform Scripts
local sub_platform  = {
    windows         = current_dir .. "windows.lua",
    linux           = current_dir .. "linux.lua",
    macosx          = current_dir .. "macos.lua",
    emscripten      = current_dir .. "emscripten.lua",
}

-- @brief Get Compute Feature Lists.
--
-- @return Returns Compute Feature Lists.
module.GetComputeFeatures = function()

    return loadfile(sub_platform[os.target()])().GetComputeFeatures() or {}

end

-- @brief Get Graphics Feature Lists.
-- 
-- @return Returns Graphics Feature Lists.
module.GetGraphicsFeatures = function()

    return loadfile(sub_platform[os.target()])().GetGraphicsFeatures() or {}

end

-- @brief Get Debugger Feature Lists.
-- 
-- @return Returns Debugger Feature Lists.
module.GetDebuggerFeatures = function()

    return loadfile(sub_platform[os.target()])().GetDebuggerFeatures() or {}

end

-- @brief Get Window Feature Lists.
-- 
-- @return Returns Window Feature Lists.
module.GetWindowFeatures = function()

    return loadfile(sub_platform[os.target()])().GetWindowFeatures() or {}

end

-- @brief Get Sub Platform Executable LinkOptions.
-- 
-- @return Returns Sub Platform Executable LinkOptions.
module.GetExecutableLinkOptions = function()

    return loadfile(sub_platform[os.target()])().GetExecutableLinkOptions() or {}

end

-- @brief Get Sub Platform Executable Links.
-- 
-- @return Returns Sub Platform Executable Links.
module.GetExecutableLinks = function()

    return loadfile(sub_platform[os.target()])().GetExecutableLinks() or {}

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

        -- Architecture x86_64
        architecture "x86_64"

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

		-- Architecture arm64
        architecture "ARM64"

        -- Use Lastest SystemVersion
		systemversion "latest"

        -- MacOS Specific Solution Macro Definitions.
		defines
		{
			-- Define Platform: MacOS.
			"NP_PLATFORM_MACOS"
		}

		-- XCode Specific Solution Settings.
		xcodebuildsettings
		{
			["MACOSX_DEPLOYMENT_TARGET"] = "13.0",       -- Minimal OS Version: 13.0
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