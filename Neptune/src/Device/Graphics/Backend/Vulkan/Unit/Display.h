/**
* @file Display.h.
* @brief The Display Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::Display Class.
    * This class defines the Vulkan::Unit::Display behaves.
    */
    class Display : public Unit<VkDisplayKHR, VkObjectType::VK_OBJECT_TYPE_DISPLAY_KHR>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Display() = default;

        /**
        * @brief Destructor Function.
        */
        ~Display() override;

    private:

        VkPhysicalDevice m_Device = VK_NULL_HANDLE;       // @brief VkPhysicalDevice.
    };
}

#endif