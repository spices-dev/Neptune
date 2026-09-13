/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Device/Graphics/Backend/Common/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::Vulkan {

    /**
    * @brief Enum of Accessible Infrastructure.
    */
    enum class EAccessibleInfrastructure : uint8_t
    {
        Instance = 0,            // @brief Instance
        ApiVersion,              // @brief ApiVersion
        PhysicalDevice,          // @brief PhysicalDevice
        Device,                  // @brief Device
        GraphicQueueFamily,      // @brief GraphicQueueFamily
        GraphicQueue,            // @brief GraphicQueue
        DescriptorPool,          // @brief DescriptorPool
        SwapChainRenderPass,     // @brief SwapChainRenderPass
        SwapChainImageUsage,     // @brief SwapChainImageUsage
        MSAASamples,             // @brief MSAASamples Count
        Allocator,               // @brief Allocator
        CheckResultFn,           // @brief CheckResultFn

        Count
    };

    using AInstance               = Graphic::Common::AccessibleInfrastructure<VkInstance,                   EAccessibleInfrastructure::Instance>;
    using AApiVersion             = Graphic::Common::AccessibleInfrastructure<uint32_t,                     EAccessibleInfrastructure::ApiVersion>;
    using APhysicalDevice         = Graphic::Common::AccessibleInfrastructure<VkPhysicalDevice,             EAccessibleInfrastructure::PhysicalDevice>;
    using ADevice                 = Graphic::Common::AccessibleInfrastructure<VkDevice,                     EAccessibleInfrastructure::Device>;
    using AGraphicQueueFamily     = Graphic::Common::AccessibleInfrastructure<uint32_t,                     EAccessibleInfrastructure::GraphicQueueFamily>;
    using AGraphicQueue           = Graphic::Common::AccessibleInfrastructure<VkQueue,                      EAccessibleInfrastructure::GraphicQueue>;
    using ADescriptorPool         = Graphic::Common::AccessibleInfrastructure<VkDescriptorPool,             EAccessibleInfrastructure::DescriptorPool>;
    using ASwapChainRenderPass    = Graphic::Common::AccessibleInfrastructure<VkRenderPass,                 EAccessibleInfrastructure::SwapChainRenderPass>;
    using ASwapChainImageUsage    = Graphic::Common::AccessibleInfrastructure<VkImageUsageFlags,            EAccessibleInfrastructure::SwapChainImageUsage>;
    using AMSAASamples            = Graphic::Common::AccessibleInfrastructure<VkSampleCountFlagBits,        EAccessibleInfrastructure::MSAASamples>;
    using AAllocator              = Graphic::Common::AccessibleInfrastructure<const VkAllocationCallbacks*, EAccessibleInfrastructure::Allocator>;
    using ACheckResultFn          = Graphic::Common::AccessibleInfrastructure<void(*)(VkResult),            EAccessibleInfrastructure::CheckResultFn>;
    
    using AContext                = Graphic::Common::AccessibleContext<EAccessibleInfrastructure>;
    
}

#endif