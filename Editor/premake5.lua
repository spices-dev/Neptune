-- @file Editor Premake.
-- @brief Defines details of the Editor Solution Building.
-- @author Spices.

solution.DefineCppExecutable("Editor", function()

	-- The Solution Files.
	files
	{
		-- SandBox Source Files.
		"src/**.h",
		"src/**.cpp",
	}

	-- Macros Definitions
	defines
	{
		-- Define Editor Assets Folder.
		'EDITOR_ASSETS_PATH=std::string("%{wks.location}/Editor/assets/")',
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"src",                                                     -- Library: Editor Source Folder.
		vendor.Neptune.includes,                                   -- Library: Neptune Source Folder.
		vendor.glm.includes,                                       -- Library: glm Source Folder.
		vendor.ImGui.includes,                                     -- Library: ImGui Source Folder.
		vendor.entt.includes,                                      -- Library: entt Source Folder.
		vendor.tracy.includes,                                     -- Library: tracy Source Folder.
	}

	-- In Visual Studio, it only works when generated a new solution, remember update solution will not works.
    -- In Rider, it will not work, needs to add environment variables manually in project configurations setting.
	debugenvs 
	{}

	-- The Solution Inherit from
	solution.Uses("Neptune")                                       -- Dependency: Neptune

	-- Configuration: Dlls.
	filter "files:**.dll"

		-- Build Action: Copy
        buildaction "Copy"

	-- Platform: Windows
	filter "system:windows"

		-- Windows Specific DLLs.
		files 
		{
			vendor.DirectX12AgilitySDK.dynamic_libraries,         -- DLL: DirectX12AgilitySDK
			vendor.WinPixEventRuntime.dynamic_libraries,          -- DLL: WinPixEventRuntime
			vendor.ffmpeg.dynamic_libraries,                      -- DLL: ffmpeg
		}

		-- Windows Specific Additional Include Folder.
		includedirs
		{}

		-- Windows Specific Solution Macro Definitions.
		defines
		{}

		-- Windows Specific Solution Dependency.
		links
		{}

		-- The Solution link options
		linkoptions
		{}

		-- The Solution build options
		buildoptions 
		{}

	-- Platform: Linux
	filter "system:linux"

		-- Linux Specific DLLs.
		files 
		{}

		-- Linux Specific Additional Include Folder.
		includedirs
		{}

		-- Linux Specific Solution Macro Definitions.
		defines
		{}

		-- Linux Specific Solution Dependency.
		links
		{}

		-- The Solution link options
		linkoptions
		{}

		-- The Solution build options
		buildoptions 
		{}

	-- Platform: Emscripten
	filter "system:emscripten"

		-- Emscripten Specific DLLs.
		files 
		{}

		-- Emscripten Specific Additional Include Folder.
		includedirs
		{}

		-- Emscripten Specific Solution Macro Definitions.
		defines
		{}

		-- Emscripten Specific Solution Dependency.
		links
		{}

		-- The Solution link options
		linkoptions
		{}

		-- The Solution build options
		buildoptions
		{}

		-- Configuration: Debug
		filter {"system:emscripten", "configurations:Debug"}

			-- The Solution debug link options
			linkoptions
			{
				"-gsource-map",                                              -- Map Source to c++
				"-gseparate-dwarf=%{cfg.targetdir}/%{prj.name}.debug.wasm",  -- Generate debug symbol version wasm
				"--emit-symbol-map",                                         -- Export symbol
			}

	-- Configuration: Debug
	filter "configurations:Debug"

		-- Debug Specific Solution Macro Definitions.
		defines
		{
			platform.GetProfilerFeatures(),
		}

		-- Platform: Emscripten
		filter {"configurations:Debug", "system:emscripten"}

			-- The Solution PostCommands
			postbuildcommands {

				-- Create target directory.
				--os.host() == "windows" and '' or 'mkdir -p "%{wks.location}/Nepnep/public/wasm/Debug/"',

				-- Copy js and wasm to Nepnep.
				--os.host() == "windows" and 'xcopy /Y /I "%{cfg.targetdir}\\" "%{wks.location}/Nepnep/public/wasm/Debug\\"'
				--	or 'cp -rf "%{cfg.targetdir}/." "%{wks.location}/Nepnep/public/wasm/Debug/"'
			}

	-- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines
		{}

		-- Platform: Emscripten
		filter {"configurations:Release", "system:emscripten"}

			-- The Solution PostCommands
			postbuildcommands {

				-- Create target directory.
				--os.host() == "windows" and '' or 'mkdir -p "%{wks.location}/Nepnep/public/wasm/Release/"',

				-- Copy js and wasm to Nepnep.
				--os.host() == "windows" and 'xcopy /Y /I "%{cfg.targetdir}\\" "%{wks.location}/Nepnep/public/wasm/Release\\"'
				--	or 'cp -rf "%{cfg.targetdir}/." "%{wks.location}/Nepnep/public/wasm/Release/"'
			}

	filter {}

end)