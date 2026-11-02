/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
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
    };
}