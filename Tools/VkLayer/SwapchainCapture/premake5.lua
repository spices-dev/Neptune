-- @file SwapchainCapture Premake.
-- @brief Defines details of the SwapchainCapture Solution Building.
-- @author Spices.

local layerName = "vk_layer_swapchain_capture"
local manifest  = layerName .. ".json"

solution.DefineCppSharedLibrary("SwapchainCapture", function()

	-- The Solution Target Name.
	targetname(layerName)

	-- The Solution Files.
	files
	{
		-- Editor Source Files.
		"src/**.h",
		"src/**.cpp",
		manifest,
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

	-- Configuration: Json.
	filter("files:" .. manifest)

		-- Build Action: Copy
        buildaction "Copy"

end)