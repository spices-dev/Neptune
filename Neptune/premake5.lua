-- @file Neptune Premake.
-- @brief Defines details of the Neptune Solution Building.
-- @author Spices.

solution.DefineCppStaticLibrary("Neptune", function()

	--compiler.EnableMoreWarning()     -- Enable Compiler Warning.

	filter { "toolset:msc*" }
		pchheader "Pchheader.h"      -- PreCompiler Header File.

	filter { "toolset:not msc*" }
		pchheader "src/Pchheader.h"  -- PreCompiler Header File.

	filter {}

	pchsource "src/Pchheader.cpp"    -- PreCompiler Cpp File.

	-- The Solution Files.
	files
	{
		-- Engine Source Files.
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",

		-- Engine Shader Headers.
		"assets/Shaders/src/Header/**.h",

		-- Library: std_image Files.
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",

		-- Library: ImGuizmo Files.
		"vendor/ImGuizmo/ImGuizmo.cpp",
		"vendor/ImGuizmo/ImGuizmo.h",

		-- Library: IconFontCppHeaders Files.
		"vendor/IconFontCppHeaders/**.h",

		-- Library: tinyply Files.
		"vendor/tinyply/source/tinyply.h",
	}

	-- Macros Definitions
	defines
	{
		-- Define Engine Assets Folder.
		'NEPTUNE_ASSETS_PATH=std::string("' .. path.translate(os.getcwd(), "/") .. '/assets/")',

		-- Define Engine Logs Folder.
		'NEPTUNE_CONSOLElOGFILE_PATH=std::string("saved/ConsoleLog/")',

		-- Define Engine Extent Processes Folder.
		'NEPTUNE_EXTENT_PROCESS_PATH=std::string("' .. path.translate(os.getcwd(), "/") .. '/../vendor/")',

		platform.GetComputeFeatures(),
		platform.GetGraphicsFeatures(),
		platform.GetWindowFeatures(),
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		vendor.Neptune.includes,                              -- Library: Neptune Source Folder.
	}

	-- The Solution Additional External Include Folder.
	externalincludedirs
	{
		vendor.glm.includes,                                  -- Library: glm Source Folder.
		vendor.vma.includes,                                  -- Library: vma Source Folder.
		vendor.stb_image.includes,                            -- Library: stb_image Source Folder.
		vendor.ImGui.includes,                                -- Library: ImGui Source Folder.
		vendor.entt.includes,                                 -- Library: entt Source Folder.
		vendor.yaml_cpp.includes,                             -- Library: yaml_cpp Source Folder.
		vendor.rapidyaml.includes,                            -- Library: rapidyaml Source Folder.
		vendor.ImPlot.includes,                               -- Library: ImPlot Source Folder.
		vendor.spdlog.includes,                               -- Library: spdlog Source Folder.
		vendor.ImGuizmo.includes,                             -- Library: ImGuizmo Source Folder.
		vendor.tracy.includes,                                -- Library: tracy Source Folder.
		vendor.IconFontCppHeaders.includes,                   -- Library: IconFontCppHeaders Source Folder.
		vendor.tinyply.includes,                              -- Library: tinyply Source Folder.
	}

	-- The Solution Dependency
	links
	{}

	-- Library: std_image is included this solution, do not use PreCompiler Header.
	filter "files:vendor/stb_image/**.cpp"
		enablepch "Off"

	-- Library: ImGuizmo is included this solution, do not use PreCompiler Header.
	filter "files:vendor/ImGuizmo/**.cpp"
		enablepch "Off"

	-- Platform: Windows
	filter "system:windows"

		-- The Solution Additional External Include Folder.
		externalincludedirs
		{
			vendor.GLFW.includes,                                 -- Library: GLFW Source Folder.
			vendor.Vulkan_Headers.includes,                       -- Library: VulkanSDK Source Folder.
			vendor.Glad.includes,                                 -- Library: Glad Source Folder.
			vendor.DirectX_Headers.includes,                      -- Library: DirectX-Headers Source Folder.
			vendor.WinPixEventRuntime.includes,                   -- Library: WinPixEventRuntime Source Folder.
			vendor.AdaptiveCpp.includes,                          -- Library: AdaptiveCpp Source Folder.
			vendor.ffmpeg.includes,                               -- Library: ffmpeg Source Folder.
			vendor.RenderDoc.includes,                            -- Library: RenderDoc Source Folder.
		}

		-- Windows Specific Additional Library Folder.
		libdirs
		{}

		-- Windows Specific Solution Macro Definitions.
		defines
		{}

		-- Windows nuget packages.
		nuget
		{}

		-- Windows Specific Solution Dependency.
		links
		{}

		-- Windows Specific build options
		buildoptions
		{}

		-- Windows Specific make settings
		makesettings 
		{
            "LINKCMD = $(file > $(OBJDIR)objects.rsp,$(OBJECTS)) $(AR) rcs $(TARGET) @$(OBJDIR)objects.rsp"    -- Enable response file
        }

	-- Platform: Linux
	filter "system:linux"

		-- The Solution Additional External Include Folder.
		externalincludedirs
		{
			vendor.GLFW.includes,                                      -- Library: GLFW Source Folder.
			vendor.Vulkan_Headers.includes,                            -- Library: VulkanSDK Source Folder.
			vendor.Glad.includes,                                      -- Library: Glad Source Folder.
			vendor.RenderDoc.includes,                                 -- Library: RenderDoc Source Folder.
		}

		-- Linux Specific Additional Library Folder.
		libdirs
		{}

		-- Linux Specific Solution Macro Definitions.
		defines
		{}

		-- Linux Specific Solution Dependency.
		links
		{}

		-- Linux Specific build options
		buildoptions 
		{}

		-- Linux Specific make settings
		makesettings 
		{
            "LINKCMD = $(file > $(OBJDIR)objects.rsp,$(OBJECTS)) $(AR) rcs $(TARGET) @$(OBJDIR)objects.rsp"     -- Enable response file
        }

	-- Platform: MacOS
	filter "system:macosx"

		-- The Solution Additional External Include Folder.
		externalincludedirs
		{
			vendor.GLFW.includes,                                      -- Library: GLFW Source Folder.
			vendor.Vulkan_Headers.includes,                            -- Library: VulkanSDK Source Folder.
			vendor.Glad.includes,                                      -- Library: Glad Source Folder.
			vendor.metal_cpp.includes,                                 -- Library: metal-cpp Source Folder.
			vendor.RenderDoc.includes,                                 -- Library: RenderDoc Source Folder.
		}

		-- MacOS Specific Additional Library Folder.
		libdirs
		{}

		-- MacOS Specific Solution Macro Definitions.
		defines
		{}

		-- MacOS Specific Solution Dependency.
		links
		{}

		-- MacOS Specific build options
		buildoptions 
		{}

		-- MacOS Specific make settings
		makesettings 
		{
            "LINKCMD = $(file > $(OBJDIR)objects.rsp,$(OBJECTS)) $(AR) rcs $(TARGET) @$(OBJDIR)objects.rsp"     -- Enable response file
        }

	-- Platform: Emscripten
	filter "system:emscripten"

		-- The Solution Additional External Include Folder.
		externalincludedirs
		{
			vendor.emscripten.includes,                                -- Library: emscripten Header Folder.
			vendor.emscripten_glfw.includes,                           -- Library: emscripten_glfw Header Folder.
			vendor.emdawnwebgpu.includes,                              -- Library: emdawnwebgpu Header Folder.
		}

		-- The Solution Additional Library Folder.
		libdirs
		{}

		-- Emscripten Specific Solution Macro Definitions.
		defines
		{}

		-- Emscripten Specific Solution Dependency.
		links
		{}

		-- Emscripten Specific build options
		buildoptions
		{}

		-- Emscripten Specific make settings
		makesettings 
		{
            "LINKCMD = $(file > $(OBJDIR)objects.rsp,$(OBJECTS)) emar rcs $(TARGET) @$(OBJDIR)objects.rsp"       -- Enable response file
        }

	-- Platform: Android
	filter "system:android"

		-- The Solution Additional External Include Folder.
		externalincludedirs
		{}

		-- Android Specific Additional Library Folder.
		libdirs
		{}

		-- Android Specific Solution Macro Definitions.
		defines
		{}

		-- Android Specific Solution Dependency.
		links
		{}

		-- Android Specific build options
		buildoptions 
		{}

		-- Android Specific make settings
		makesettings 
		{
            "LINKCMD = $(file > $(OBJDIR)objects.rsp,$(OBJECTS)) $(AR) rcs $(TARGET) @$(OBJDIR)objects.rsp"     -- Enable response file
        }

	-- Configuration: Debug
	filter "configurations:Debug"

		-- Debug Specific Solution Macro Definitions.
		defines
		{
			platform.GetDebuggerFeatures(),
		}

		-- Debug Specific Solution Dependency
		links
		{}
		
	-- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines 
		{}

		-- Release Specific Solution Dependency
		links
		{}

	-- Public Config
	usage "PUBLIC"

        links
		{
			"ImGui",                                                       -- Dependency: imgui
			"yaml-cpp",                                                    -- Dependency: yaml-cpp
			"implot",                                                      -- Dependency: implot
		}

		-- Platform: Windows
		filter "system:windows"

			-- Windows Specific Library Folder.
			libdirs
			{
				vendor.Vulkan.library_dirs,                                -- Library: VulkanSDK.
				vendor.WinPixEventRuntime.library_dirs,                    -- Library: WinPixEventRuntime.
				vendor.ffmpeg.library_dirs,                                -- Library: ffmpeg.
			}

			-- Windows Specific Solution Dependency.
			links
			{
				vendor.Vulkan.libraries,                                   -- Dependency: Vulkan
				vendor.Direct3D11.libraries,                               -- Dependency: Direct3D11
				vendor.DirectX12AgilitySDK.libraries,                      -- Dependency: DirectX12AgilitySDK
				vendor.WinPixEventRuntime.libraries,                       -- Dependency: WinPixEventRuntime
				vendor.ffmpeg.libraries,                                   -- Dependency: ffmpeg

				"GLFW",                                                    -- Dependency: GLFW
				"Glad",                                                    -- Dependency: Glad
				"tracy",                                                   -- Dependency: tracy
			}

			-- Configuration: Debug
			filter {"system:windows", "configurations:Debug"}

				-- Debug Specific Solution Dependency
				links
				{}
        
			-- Configuration: Release
			filter {"system:windows", "configurations:Release"}

				-- Release Specific Solution Dependency
				links
				{}

		-- Platform: Linux
		filter "system:linux"

			-- Linux Specific Additional Library Folder.
			libdirs
			{
				vendor.Vulkan.library_dirs,                                -- Library: VulkanSDK.
			}

			-- Linux Specific Runtime Additional Library Folder.
			runpathdirs
			{
				vendor.Vulkan.library_dirs,                                -- Runtime Library: VulkanSDK.
			}

			-- Linux Specific Solution Dependency.
			links
			{
				vendor.Vulkan.libraries,                                   -- Dependency: vulkan
				
				"GLFW",                                                    -- Dependency: GLFW
				"Glad",                                                    -- Dependency: Glad
				"tracy",                                                   -- Dependency: tracy
			}

		-- Platform: MacOS
		filter "system:macosx"

			-- MacOS Specific Additional Library Folder.
			libdirs
			{
				vendor.Vulkan.library_dirs,                                -- Library: VulkanSDK.
			}

			-- MacOS Specific Runtime Additional Library Folder.
			runpathdirs
			{
				vendor.Vulkan.library_dirs,                                -- Runtime Library: VulkanSDK.
			}

			-- MacOS Specific Solution Dependency.
			links
			{
				vendor.Vulkan.libraries,                                   -- Dependency: vulkan
				
				"GLFW",                                                    -- Dependency: GLFW
				"Glad",                                                    -- Dependency: Glad
				"tracy",                                                   -- Dependency: tracy
			}

		-- Platform: Emscripten
		filter "system:emscripten"

			-- Emscripten Specific Solution Dependency.
			links
			{
				"tracy",                                                   -- Dependency: tracy
			}

		-- Platform: Android
		filter "system:android"

			-- Android Specific Solution Dependency.
			links
			{
				"tracy",                                                   -- Dependency: tracy
			}

	filter {}

end)