-- @file Runtime Premake.
-- @brief Defines details of the Runtime Solution Building.
-- @author Spices.

project "Runtime"
	kind "ConsoleApp"           -- Use executeable program.
	language "C++"				-- Use C++.
	cppdialect "C++20"			-- Use C++20.
	staticruntime "On"			-- Use Runtime Library: MTD.

	-- Building Output Folder.
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	-- Building Object Folder.
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- Enable Multi Processor Compile
	multiprocessorcompile "On"

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
		-- Define Runtime Assets Folder.
		'RUNTIME_ASSETS_PATH=std::string("%{wks.location}/Runtime/assets/")',
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"%{vendor.includes.Neptune}",                              -- Neptune Source Folder.
		"src",                                                     -- UnitTest Source Folder.
		"%{vendor.includes.glm}",                                  -- Library: glm Source Folder.
		"%{vendor.includes.entt}",                                 -- Library: entt Source Folder.
		"%{vendor.includes.tracy}",                                -- Library: tracy Source Folder.
	}

	-- In Visual Studio, it only works when generated a new solution, remember update solution will not works.
    -- In Rider, it will not work, needs to add environment variables manually in project configurations setting.
	debugenvs 
	{}

	-- The Solution Inherit from
	solution.Uses("Neptune")                   -- Dependency: Neptune

	-- Platform: Windows
	filter "system:windows"

		-- The Solution Additional Include Folder.
		includedirs
		{}

		-- Windows Specific Solution Macro Definitions.
		defines
		{}

		-- The Solution link options
		linkoptions
		{
			platform.GetExecutableLinkOptions()
		}

		-- The Solution build options
		buildoptions 
		{}

	-- Platform: Linux
	filter "system:linux"

		-- The Solution Additional Include Folder.
		includedirs
		{}

		-- Linux Specific Solution Macro Definitions.
		defines
		{}

		-- The Solution link options
		linkoptions
		{
			platform.GetExecutableLinkOptions()
		}

		-- The Solution build options
		buildoptions 
		{}

	-- Platform: Emscripten
	filter "system:emscripten"

		-- The Solution Additional Include Folder.
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
		{
			platform.GetExecutableLinkOptions()
		}

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