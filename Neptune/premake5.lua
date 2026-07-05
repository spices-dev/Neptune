-- @file Neptune Premake.
-- @brief Defines details of the Neptune Solution Building.
-- @author Spices.

solution.DefineCppStaticLibrary("Neptune", function()

	pchheader "Pchheader.h"          -- PreCompiler Header File.
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
	}

	-- Macros Definitions
	defines
	{
		-- Define Engine Assets Folder.
		--'NEPTUNE_ASSETS_PATH=std::string("' .. path.translate(os.getcwd(), "/") .. '/assets/")',

		-- Define Engine Logs Folder.
		--'NEPTUNE_CONSOLElOGFILE_PATH=std::string("saved/ConsoleLog/")',

		-- Define Engine Extent Processes Folder.
		--'NEPTUNE_EXTENT_PROCESS_PATH=std::string("' .. path.translate(os.getcwd(), "/") .. '/../vendor/")',

		platform.GetComputeFeatures(),
		platform.GetGraphicsFeatures(),
		platform.GetWindowFeatures(),
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"src",                                                     -- Neptune Source Folder.
		"%{vendor.includes.NeptuneShader}",                        -- Neptune Shader Source Folder.
		"%{vendor.includes.glm}",                                  -- Library: glm Source Folder.
		"%{vendor.includes.vma}",                                  -- Library: vma Source Folder.
		"%{vendor.includes.stb_image}",                            -- Library: stb_image Source Folder.
		"%{vendor.includes.ImGui}",                                -- Library: ImGui Source Folder.
		"%{vendor.includes.entt}",                                 -- Library: entt Source Folder.
		"%{vendor.includes.yaml_cpp}",                             -- Library: yaml_cpp Source Folder.
		"%{vendor.includes.rapidyaml}",                            -- Library: rapidyaml Source Folder.
		"%{vendor.includes.ImPlot}",                               -- Library: ImPlot Source Folder.
		"%{vendor.includes.spdlog}",                               -- Library: spdlog Source Folder.
		"%{vendor.includes.ImGuizmo}",                             -- Library: ImGuizmo Source Folder.
		"%{vendor.includes.tracy}",                                -- Library: tracy Source Folder.
		"%{vendor.includes.IconFontCppHeaders}",                   -- Library: IconFontCppHeaders Source Folder.
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

		-- The Solution Additional Include Folder.
		includedirs
		{
            "%{vendor.includes.shaderc}",                              -- Library: shaderc Source Folder.
            "%{vendor.includes.shaderc}/libshaderc/include",           -- Library: shaderc libshaderc Source Folder.
            "%{vendor.includes.shaderc}/libshaderc_util/include",      -- Library: shaderc libshaderc_util Source Folder.
            "%{vendor.includes.glslang}",                              -- Library: glslang Source Folder.
			"%{vendor.includes.GLFW}",                                 -- Library: GLFW Source Folder.
			"%{vendor.includes.VulkanSDK}",                            -- Library: VulkanSDK Source Folder.
			"%{vendor.includes.Glad}",                                 -- Library: Glad Source Folder.
			"%{vendor.includes.DirectX12AgilitySDK}",                  -- Library: DirectX12AgilitySDK Source Folder.
			"%{vendor.includes.WinPixEventRuntime}",                   -- Library: WinPixEventRuntime Source Folder.
			"%{vendor.includes.AdaptiveCpp}",                          -- Library: AdaptiveCpp Source Folder.
		}

		-- Windows Specific Additional Library Folder.
		libdirs
		{}

		-- Windows Specific Solution Macro Definitions.
		defines
		{}

		-- Windows nuget packages.
		nuget
		{
			"%{vendor.nugets.DirectX12AgilitySDK}",                    -- Dependency: Direct3D12
			"%{vendor.nugets.WinPixEventRuntime}",                     -- Dependency: WinPixEventRuntime
		}

		-- Windows Specific Solution Dependency.
		links
		{}

		-- The Solution build options
		buildoptions 
		{}

	-- Platform: Linux
	filter "system:linux"

		-- The Solution Additional Include Folder.
		includedirs
		{
            "%{vendor.includes.shaderc}",                              -- Library: shaderc Source Folder.
            "%{vendor.includes.shaderc}/libshaderc/include",           -- Library: shaderc libshaderc Source Folder.
            "%{vendor.includes.shaderc}/libshaderc_util/include",      -- Library: shaderc libshaderc_util Source Folder.
            "%{vendor.includes.glslang}",                              -- Library: glslang Source Folder.
			"%{vendor.includes.GLFW}",                                 -- Library: GLFW Source Folder.
			"%{vendor.includes.VulkanSDK}",                            -- Library: VulkanSDK Source Folder.
			"%{vendor.includes.Glad}",                                 -- Library: Glad Source Folder.
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

		-- The Solution build options
		buildoptions 
		{}

	-- Platform: Emscripten
	filter "system:emscripten"

		-- The Solution Additional Include Folder.
		includedirs
		{
			"%{vendor.includes.emscripten}",                           -- Library: emscripten Header Folder.
			"%{vendor.includes.emscripten_glfw}/include",              -- Library: emscripten_glfw Header Folder.
			"%{vendor.includes.emscripten_glfw}/external",             -- Library: emscripten_glfw Header Folder.
			"%{vendor.includes.emdawnwebgpu}",                         -- Library: emdawnwebgpu Header Folder.
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

		-- The Solution build options
		buildoptions
		{}

		-- The Solution make settings
		makesettings 
		{
            "LINKCMD = $(file > $(OBJDIR)objects.rsp,$(OBJECTS)) emar rcs $(TARGET) @$(OBJDIR)objects.rsp"   -- Enable response file
        }

	-- Configuration: Debug
	filter "configurations:Debug"

		-- Debug Specific Solution Macro Definitions.
		defines
		{
			platform.GetProfilerFeatures(),
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
			"yaml-cpp",                                                    -- Dependency: yaml-cpp
			"implot",                                                      -- Dependency: implot
		}

		-- Platform: Windows
		filter "system:windows"

			-- Windows Specific Library Folder.
			libdirs
			{
				"%{vendor.library_dirs.VulkanSDK}",                        -- Library: VulkanSDK.
				"%{vendor.library_dirs.WinPixEventRuntime}",               -- Library: WinPixEventRuntime.
			}

			-- Windows Specific Solution Dependency.
			links
			{
				"%{vendor.libraries.vulkan}",                              -- Dependency: vulkan
				"%{vendor.libraries.dxgi}",                                -- Dependency: dxgi
				"%{vendor.libraries.d3d11}",                               -- Dependency: d3d11
				"%{vendor.libraries.d3dcompiler}",                         -- Dependency: d3dcompiler
				"%{vendor.libraries.d3d12}",                               -- Dependency: d3d12
				"%{vendor.libraries.WinPixEventRuntime}",                  -- Dependency: WinPixEventRuntime
				
				"ImGui_Vulkan",                                            -- Dependency: imgui
				"ImGui_OpenGL",                                            -- Dependency: imgui
				"ImGui_Direct3D11",                                        -- Dependency: imgui
				"ImGui_Direct3D12",                                        -- Dependency: imgui
				"GLFW",                                                    -- Dependency: GLFW
				"Glad",                                                    -- Dependency: Glad
				"tracy",                                                   -- Dependency: tracy
				"shaderc",                                                 -- Dependency：shaderc 
			}

			-- Configuration: Debug
			filter {"system:windows", "configurations:Debug"}

				-- Debug Specific Solution Dependency
				links
				{
					"%{vendor.libraries.shaderc_debug}",                   -- Dependency: shaderc_debug
				}
        
			-- Configuration: Release
			filter {"system:windows", "configurations:Release"}

				-- Release Specific Solution Dependency
				links
				{
					"%{vendor.libraries.shaderc_release}",                 -- Dependency: shaderc_release
				}

		-- Platform: Linux
		filter "system:linux"

			-- Linux Specific Additional Library Folder.
			libdirs
			{
				"%{vendor.library_dirs.VulkanSDK}",                        -- Library: VulkanSDK.
			}

			-- Linux Specific Solution Dependency.
			links
			{
				"%{vendor.libraries.vulkan}",                              -- Dependency: vulkan
				
				"ImGui_Vulkan",                                            -- Dependency: imgui
				"ImGui_OpenGL",                                            -- Dependency: imgui
				"GLFW",                                                    -- Dependency: GLFW
				"Glad",                                                    -- Dependency: Glad
				"tracy",                                                   -- Dependency: tracy
				"shaderc",                                                 -- Dependency：shaderc
				"%{vendor.libraries.shaderc}",                             -- Dependency: shaderc_debug
			}

		-- Platform: Emscripten
		filter "system:emscripten"

			-- Emscripten Specific Solution Dependency.
			links
			{
				"ImGui_WebGPU",                                            -- Dependency: imgui
				"tracy",                                                   -- Dependency: tracy
			}

	filter {}

end)