/**
* @file DeviceTable.h.
* @brief The DeviceTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Infrastructure.h"
#include "MultiInstance.h"
#include "Vulkan/Unit/Device.h"

#include <vulkan/utility/vk_dispatch_table.h>

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
        
        UP<Unit::Device>         m_Device;          // @brief this unit Device.
        VkPhysicalDevice         vkPhysicalDevice;  // @brief VkPhysicalDevice.
        VkuDeviceDispatchTable_  m_Table;           // @brief VkuDeviceDispatchTable_.
    };

}