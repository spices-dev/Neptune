/**
* @file DeviceTable.h.
* @brief The DeviceTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "MultiInstance.h"
#include "Vulkan/Unit/Device.h"

namespace Neptune::Vulkan {

    using IDeviceTable = IInfrastructure<MultiInstance<void*, class DeviceTable>, 1u>;
    
    /**
    * @brief Vulkan::DeviceTable Class.
    * This class defines the Vulkan::DeviceTable behaves.
    */
    class DeviceTable : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        */
        DeviceTable() = default;

        /**
        * @brief Destructor Function.
        */
        ~DeviceTable() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Device::Handle& Handle() const { return m_Device->GetHandle(); }

    public:
        
        UP<Unit::Device>                 m_Device;                      // @brief this unit Device.
        PFN_vkGetDeviceProcAddr          vkGetDeviceProcAddr;           // @brief PFN_vkGetDeviceProcAddr.
        VkPhysicalDevice                 vkPhysicalDevice;              // @brief VkPhysicalDevice.
        
        PFN_vkCreateSwapchainKHR         vkCreateSwapchainKHR;          // @brief PFN_vkCreateSwapchainKHR.
        PFN_vkDestroySwapchainKHR        vkDestroySwapchainKHR;         // @brief PFN_vkDestroySwapchainKHR.
        PFN_vkQueuePresentKHR            vkQueuePresentKHR;             // @brief PFN_vkQueuePresentKHR.
        PFN_vkGetSwapchainImagesKHR      vkGetSwapchainImagesKHR;       // @brief PFN_vkGetSwapchainImagesKHR.
        PFN_vkCreateCommandPool          vkCreateCommandPool;           // @brief PFN_vkCreateCommandPool.
        PFN_vkDestroyCommandPool         vkDestroyCommandPool;          // @brief PFN_vkDestroyCommandPool.
        PFN_vkAllocateCommandBuffers     vkAllocateCommandBuffers;      // @brief PFN_vkAllocateCommandBuffers.
        PFN_vkFreeCommandBuffers         vkFreeCommandBuffers;          // @brief PFN_vkFreeCommandBuffers.
        PFN_vkBeginCommandBuffer         vkBeginCommandBuffer;          // @brief PFN_vkBeginCommandBuffer.
        PFN_vkEndCommandBuffer           vkEndCommandBuffer;            // @brief PFN_vkEndCommandBuffer.
        PFN_vkQueueSubmit                vkQueueSubmit;                 // @brief PFN_vkQueueSubmit.
        PFN_vkDeviceWaitIdle             vkDeviceWaitIdle;              // @brief PFN_vkDeviceWaitIdle.
        PFN_vkCreateSemaphore            vkCreateSemaphore;             // @brief PFN_vkCreateSemaphore.
        PFN_vkDestroySemaphore           vkDestroySemaphore;            // @brief PFN_vkDestroySemaphore.
    };

}