/**
* @file Core.h.
* @brief Neptune VkLayer Core Macro.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#define VK_NO_PROTOTYPES

#include <vulkan/vulkan.h>

extern "C" { DLL_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(struct VkNegotiateLayerInterface* pVersionStruct); }

#include <vulkan/vk_layer.h>
#include <Vulkan/vk_enum_string_helper.h>

namespace Neptune {

#define VULKAN_CHECK(expr)                                                        \
    do {                                                                          \
        const VkResult _vk_result = (expr);                                       \
        if (_vk_result != VK_SUCCESS) {                                           \
            NEPTUNE_LOG_CORE(E) << "Result: " << string_VkResult(_vk_result)      \
                                << ", File: " << __FILE__                         \
                                << ", Line: " << __LINE__                         \
                                << ", Func: " << __FUNCTION__;                    \
            return _vk_result;                                                    \
        }                                                                         \
    } while (0);
    
}