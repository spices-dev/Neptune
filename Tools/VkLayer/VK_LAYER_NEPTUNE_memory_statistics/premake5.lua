-- @file VK_LAYER_NEPTUNE_memory_statistics Premake.
-- @brief Defines details of the VK_LAYER_NEPTUNE_memory_statistics Solution Building.
-- @author Spices.

local layerName = "VK_LAYER_NEPTUNE_memory_statistics"

solution.DefineCppSharedLibrary(layerName, function()

 	-- Building Output Folder.
	targetdir("%{wks.location}/bin/" .. solution.OutputDirectory .. "/Tools/VkLayer")

	-- The Solution Target Name.
	targetname(layerName)

	-- The Solution Files.
	files
	{
		-- Source Files.
		"src/**.h",
		"src/**.cpp",

		-- Core Source Files.
		"../src/**.h",
		"../src/**.cpp",
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"src",                                                     -- Library: Source Folder.
		"../src",                                                  -- Library: Core Source Folder.
	}

	-- The Solution Additional External Include Folder.
	externalincludedirs
	{
		vendor.Vulkan_Headers.includes,                           -- Library: VulkanSDK Source Folder.
	}

end)