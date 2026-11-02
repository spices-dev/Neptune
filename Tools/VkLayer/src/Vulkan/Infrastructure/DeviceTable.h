/**
* @file DeviceTable.h.
* @brief The DeviceTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Vulkan/Unit/Device.h"

#include <vector>

namespace Neptune::Vulkan {

    using IDeviceTable = IInfrastructure<class DeviceTable, 1u>;
    
    /**
    * @brief Vulkan::DeviceTable Class.
    * This class defines the Vulkan::DeviceTable behaves.
    */
    class DeviceTable : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] device Unit::Device.
        */
        DeviceTable(const SP<Unit::Device>& device) : m_Device(device) {}

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

    private:

        SP<Unit::Device>                 m_Device;                      // @brief this unit Device.

    public:
        
        PFN_vkGetDeviceProcAddr          vkGetDeviceProcAddr;           // @brief PFN_vkGetDeviceProcAddr.
        VkPhysicalDevice                 vkPhysicalDevice;              // @brief VkPhysicalDevice.
        
        PFN_vkCreateSwapchainKHR         vkCreateSwapchainKHR;          // @brief PFN_vkCreateSwapchainKHR.
        PFN_vkDestroySwapchainKHR        vkDestroySwapchainKHR;         // @brief PFN_vkDestroySwapchainKHR.
        PFN_vkQueuePresentKHR            vkQueuePresentKHR;             // @brief PFN_vkQueuePresentKHR.
        PFN_vkGetSwapchainImagesKHR      vkGetSwapchainImagesKHR;       // @brief PFN_vkGetSwapchainImagesKHR.
    };

}