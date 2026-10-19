/**
* @file ExtensionHeader.h.
* @brief The ExtensionHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "DescriptorBuffer.h"
#include "DescriptorHeap.h"
#include "DeviceFault.h"
#include "HDR.h"
#include "OpticalFlow.h"
#include "RayTracing.h"
#include "SwapChain.h"
#include "VideoDecode.h"
#include "VideoEncode.h"
#include "SamplerYcbcrConversion.h"
#include "Maintenance1.h"
#include "Maintenance4.h"
#include "Maintenance5.h"
#include "MemoryBudget.h"
#include "DebugUtils.h"
#include "BufferDeviceAddress.h"
#include "DescriptorIndexing.h"
#include "Vulkan11.h"
#include "Vulkan13.h"
#include "Portability.h"
#include "Queue.h"
#include "LayerSetting.h"
#include "DynamicRendering.h"
#include "ExternalMemoryHost.h"
#include "CopyMemoryIndirect.h"
#include "DeviceGeneratedCommands.h"
#include "GetPhysicalDeviceProperties2.h"
#include "PageableDeviceLocalMemory.h"
#include "GetSurfaceCapabilities2.h"
#include "CreateRenderPass2.h"
#include "DynamicRenderingLocalRead.h"
#include "ScalarBlockLayout.h"
#include "TimelineSemaphore.h"
#include "Synchronization2.h"
#include "PresentTiming.h"
#include "UnifiedImageLayouts.h"
#include "MeshShader.h"
#include "DeviceAddressCommands.h"
#include "Subgroup.h"
#include "SubgroupSizeControl.h"
#include "SubgroupPartitioned.h"
#include "SubgroupRotate.h"
#include "DeviceGroup.h"
#include "DeviceAddressBindingReport.h"

// Device
//m_ExtensionProperties.push_back(VK_KHR_SHADER_CLOCK_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SPIRV_1_4_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME);

#endif