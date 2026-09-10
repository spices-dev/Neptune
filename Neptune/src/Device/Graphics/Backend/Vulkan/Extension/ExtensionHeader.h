/**
* @file ExtensionHeader.h.
* @brief The ExtensionHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Device/Graphics/Backend/Vulkan/Extension/DescriptorBuffer.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DescriptorHeap.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DeviceFault.h"
#include "Device/Graphics/Backend/Vulkan/Extension/HDR.h"
#include "Device/Graphics/Backend/Vulkan/Extension/OpticalFlow.h"
#include "Device/Graphics/Backend/Vulkan/Extension/RayTracing.h"
#include "Device/Graphics/Backend/Vulkan/Extension/SwapChain.h"
#include "Device/Graphics/Backend/Vulkan/Extension/VideoDecode.h"
#include "Device/Graphics/Backend/Vulkan/Extension/VideoEncode.h"
#include "Device/Graphics/Backend/Vulkan/Extension/SamplerYcbcrConversion.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Maintenance1.h"
#include "Device/Graphics/Backend/Vulkan/Extension/MemoryBudget.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DebugUtils.h"
#include "Device/Graphics/Backend/Vulkan/Extension/BufferDeviceAddress.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DescriptorIndexing.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Vulkan13.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Portability.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"
#include "Device/Graphics/Backend/Vulkan/Extension/LayerSetting.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DynamicRendering.h"
#include "Device/Graphics/Backend/Vulkan/Extension/ExternalMemoryHost.h"
#include "Device/Graphics/Backend/Vulkan/Extension/CopyMemoryIndirect.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DeviceGeneratedCommands.h"
#include "Device/Graphics/Backend/Vulkan/Extension/GetPhysicalDeviceProperties2.h"
#include "Device/Graphics/Backend/Vulkan/Extension/PageableDeviceLocalMemory.h"
#include "Device/Graphics/Backend/Vulkan/Extension/GetSurfaceCapabilities2.h"
#include "Device/Graphics/Backend/Vulkan/Extension/CreateRenderPass2.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DynamicRenderingLocalRead.h"
#include "Device/Graphics/Backend/Vulkan/Extension/ScalarBlockLayout.h"
#include "Device/Graphics/Backend/Vulkan/Extension/TimelineSemaphore.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Synchronization2.h"
#include "Device/Graphics/Backend/Vulkan/Extension/PresentTiming.h"

// Device
//m_ExtensionProperties.push_back(VK_KHR_SHADER_CLOCK_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SPIRV_1_4_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_EXT_MESH_SHADER_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME);

#endif