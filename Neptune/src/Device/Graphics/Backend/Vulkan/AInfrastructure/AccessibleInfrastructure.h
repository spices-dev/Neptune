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

    using AInstance               = Render::Common::AccessibleInfrastructure<VkInstance,                   EAccessibleInfrastructure::Instance>;
    using APhysicalDevice         = Render::Common::AccessibleInfrastructure<VkPhysicalDevice,             EAccessibleInfrastructure::PhysicalDevice>;
    using ADevice                 = Render::Common::AccessibleInfrastructure<VkDevice,                     EAccessibleInfrastructure::Device>;
    using AGraphicQueueFamily     = Render::Common::AccessibleInfrastructure<uint32_t,                     EAccessibleInfrastructure::GraphicQueueFamily>;
    using AGraphicQueue           = Render::Common::AccessibleInfrastructure<VkQueue,                      EAccessibleInfrastructure::GraphicQueue>;
    using ADescriptorPool         = Render::Common::AccessibleInfrastructure<VkDescriptorPool,             EAccessibleInfrastructure::DescriptorPool>;
    using ASwapChainRenderPass    = Render::Common::AccessibleInfrastructure<VkRenderPass,                 EAccessibleInfrastructure::SwapChainRenderPass>;
    using ASwapChainImageUsage    = Render::Common::AccessibleInfrastructure<VkImageUsageFlags,            EAccessibleInfrastructure::SwapChainImageUsage>;
    using AMSAASamples            = Render::Common::AccessibleInfrastructure<VkSampleCountFlagBits,        EAccessibleInfrastructure::MSAASamples>;
    using AAllocator              = Render::Common::AccessibleInfrastructure<const VkAllocationCallbacks*, EAccessibleInfrastructure::Allocator>;
    using ACheckResultFn          = Render::Common::AccessibleInfrastructure<void(*)(VkResult),            EAccessibleInfrastructure::CheckResultFn>;
    
    using AContext                = Render::Common::AccessibleContext<EAccessibleInfrastructure>;
    
}

#endif