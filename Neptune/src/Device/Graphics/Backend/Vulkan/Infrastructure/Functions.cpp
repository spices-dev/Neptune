/**
* @file Functions.cpp.
* @brief The Functions Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Functions.h"
#include "Instance.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DebugUtils.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DeviceFault.h"
#include "Device/Graphics/Backend/Vulkan/Extension/RayTracing.h"
#include "Device/Graphics/Backend/Vulkan/Extension/MeshShader.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DeviceGeneratedCommands.h"
#include "Device/Graphics/Backend/Vulkan/Extension/VideoDecode.h"
#include "Device/Graphics/Backend/Vulkan/Extension/VideoEncode.h"
#include "Device/Graphics/Backend/Vulkan/Extension/OpticalFlow.h"
#include "Device/Graphics/Backend/Vulkan/Extension/HDR.h"
#include "Device/Graphics/Backend/Vulkan/Extension/CreateRenderPass2.h"

namespace Neptune::Vulkan {

	Functions::Functions(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{}

	void Functions::Init(VkInstance instance)
	{
		NEPTUNE_PROFILE_ZONE

		if(GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IDebugUtils>())
		{
			EXPLAIN_VK_FUNCTION_POINTER(vkCreateDebugUtilsMessengerEXT                  )
			EXPLAIN_VK_FUNCTION_POINTER(vkDestroyDebugUtilsMessengerEXT                 )

			EXPLAIN_VK_FUNCTION_POINTER(vkCmdBeginDebugUtilsLabelEXT                    )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdEndDebugUtilsLabelEXT                      )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdInsertDebugUtilsLabelEXT                   )

			EXPLAIN_VK_FUNCTION_POINTER(vkQueueBeginDebugUtilsLabelEXT                  )
			EXPLAIN_VK_FUNCTION_POINTER(vkQueueEndDebugUtilsLabelEXT                    )
			EXPLAIN_VK_FUNCTION_POINTER(vkQueueInsertDebugUtilsLabelEXT                 )
																			       
			EXPLAIN_VK_FUNCTION_POINTER(vkSetDebugUtilsObjectNameEXT                    )
			EXPLAIN_VK_FUNCTION_POINTER(vkSetDebugUtilsObjectTagEXT                     )
		}
		
		if(GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IDeviceFault>())
		{
			EXPLAIN_VK_FUNCTION_POINTER(vkGetDeviceFaultReportsKHR                      )
			EXPLAIN_VK_FUNCTION_POINTER(vkGetDeviceFaultDebugInfoKHR                    )
		}
		
		if(GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IRayTracing>())
		{
			EXPLAIN_VK_FUNCTION_POINTER(vkGetRayTracingShaderGroupHandlesKHR            )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdTraceRaysKHR                               )
			EXPLAIN_VK_FUNCTION_POINTER(vkCreateRayTracingPipelinesKHR                  )
			EXPLAIN_VK_FUNCTION_POINTER(vkCreateAccelerationStructureKHR                )
			EXPLAIN_VK_FUNCTION_POINTER(vkDestroyAccelerationStructureKHR               )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdBuildAccelerationStructuresKHR             )
			EXPLAIN_VK_FUNCTION_POINTER(vkCopyAccelerationStructureKHR                  )
			EXPLAIN_VK_FUNCTION_POINTER(vkGetAccelerationStructureDeviceAddressKHR      )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdWriteAccelerationStructuresPropertiesKHR   )
			EXPLAIN_VK_FUNCTION_POINTER(vkGetAccelerationStructureBuildSizesKHR         )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdCopyAccelerationStructureKHR               )
		}

		if(GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IMeshShader>())
		{
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdDrawMeshTasksEXT                           )
		}

		if(GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IDeviceGeneratedCommands>())
		{
			EXPLAIN_VK_FUNCTION_POINTER(vkCreateIndirectCommandsLayoutNV                )
			EXPLAIN_VK_FUNCTION_POINTER(vkDestroyIndirectCommandsLayoutNV               )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdExecuteGeneratedCommandsNV                 )
			EXPLAIN_VK_FUNCTION_POINTER(vkGetGeneratedCommandsMemoryRequirementsNV      )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdPreprocessGeneratedCommandsNV              )
		}

		EXPLAIN_VK_FUNCTION_POINTER(vkCmdSetCheckpointNV                            )

		EXPLAIN_VK_FUNCTION_POINTER(vkGetPhysicalDeviceCalibrateableTimeDomainsEXT  )
		EXPLAIN_VK_FUNCTION_POINTER(vkGetCalibratedTimestampsEXT                    )
		EXPLAIN_VK_FUNCTION_POINTER(vkResetQueryPool                                )

		EXPLAIN_VK_FUNCTION_POINTER(vkCopyMemoryToImageEXT                          )
		EXPLAIN_VK_FUNCTION_POINTER(vkCopyImageToMemoryEXT                          )

		if(GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IVideoDecode>() || GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IVideoEncode>())
		{
			EXPLAIN_VK_FUNCTION_POINTER(vkGetPhysicalDeviceVideoCapabilitiesKHR         )
			EXPLAIN_VK_FUNCTION_POINTER(vkCreateVideoSessionParametersKHR               )
			EXPLAIN_VK_FUNCTION_POINTER(vkDestroyVideoSessionParametersKHR              )
			EXPLAIN_VK_FUNCTION_POINTER(vkUpdateVideoSessionParametersKHR               )
			EXPLAIN_VK_FUNCTION_POINTER(vkGetPhysicalDeviceVideoFormatPropertiesKHR     )
			EXPLAIN_VK_FUNCTION_POINTER(vkGetVideoSessionMemoryRequirementsKHR          )
			EXPLAIN_VK_FUNCTION_POINTER(vkBindVideoSessionMemoryKHR                     )
			EXPLAIN_VK_FUNCTION_POINTER(vkCreateVideoSessionKHR                         )
			EXPLAIN_VK_FUNCTION_POINTER(vkDestroyVideoSessionKHR                        )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdBeginVideoCodingKHR                        )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdControlVideoCodingKHR                      )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdDecodeVideoKHR                             )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdEndVideoCodingKHR                          )
		}
		
		if(GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IOpticalFlow>())
		{
			EXPLAIN_VK_FUNCTION_POINTER(vkCreateOpticalFlowSessionNV                    )
			EXPLAIN_VK_FUNCTION_POINTER(vkDestroyOpticalFlowSessionNV                   )
			EXPLAIN_VK_FUNCTION_POINTER(vkCmdOpticalFlowExecuteNV                       )
			EXPLAIN_VK_FUNCTION_POINTER(vkGetPhysicalDeviceOpticalFlowImageFormatsNV    )
			EXPLAIN_VK_FUNCTION_POINTER(vkBindOpticalFlowSessionImageNV                 )
		}
		
		if(GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IHDR>())
		{
			EXPLAIN_VK_FUNCTION_POINTER(vkSetHdrMetadataEXT                             )
		}
	}
}

#endif