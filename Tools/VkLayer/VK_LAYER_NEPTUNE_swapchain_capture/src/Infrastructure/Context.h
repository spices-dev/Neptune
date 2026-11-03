/**
* @file Context.h.
* @brief The Context Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <vector>

namespace Neptune::Vulkan {
    
    /**
    * @brief This Layer Context Data
    */
    struct Context
    {
        VkBuffer                 buffer;             // @brief SwapChain Image Transfer Buffer.
        
        VkSemaphore              semaphore;          // @brief VkSemaphore.
    };
}