-- @file SwapchainCapture Premake.
-- @brief Defines details of the SwapchainCapture Solution Building.
-- @author Spices.

solution.DefineCppSharedLibrary("SwapChainCapture", function()

	-- The Solution Target Name.
	targetname(layerName)

	-- The Solution Files.
	files
	{
		-- Editor Source Files.
		"src/**.h",
		"src/**.cpp",
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"src",                                                     -- Library: Editor Source Folder.
	}

	-- The Solution Additional External Include Folder.
	externalincludedirs
	{
		vendor.Vulkan_Headers.includes,                           -- Library: VulkanSDK Source Folder.
	}

end)