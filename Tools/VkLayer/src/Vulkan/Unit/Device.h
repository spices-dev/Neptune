/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::Device Class.
    * This class defines the Vulkan::Unit::Device behaves.
    */
    class Device : public Unit<VkDevice, PFN_vkCreateDevice, PFN_vkDestroyDevice>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Device() = default;

        /**
        * @brief Destructor Function.
        */
        ~Device() override;
        
        /**
        * @brief Create Device.
        *
        * @param[in] physicalDevice VkPhysicalDevice.
        * @param[in] info VkDeviceCreateInfo.
        * 
        * @return Returns VkResult.
        */
        VkResult CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& info);
    };
}