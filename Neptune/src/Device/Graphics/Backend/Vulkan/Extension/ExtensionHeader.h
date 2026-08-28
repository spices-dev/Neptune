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

// Instance
//m_ExtensionProperties.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME);

// Device
//m_ExtensionProperties.push_back(VK_KHR_SHADER_CLOCK_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SPIRV_1_4_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_EXT_MESH_SHADER_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME);
//m_ExtensionProperties.push_back(VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME);

#endif