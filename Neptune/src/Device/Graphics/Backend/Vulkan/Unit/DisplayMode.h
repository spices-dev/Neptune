/**
* @file DisplayMode.h.
* @brief The DisplayMode Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::DisplayMode Class.
    * This class defines the Vulkan::Unit::DisplayMode behaves.
    */
    class DisplayMode : public Unit<VkDisplayModeKHR, VkObjectType::VK_OBJECT_TYPE_DISPLAY_MODE_KHR>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        DisplayMode() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~DisplayMode() override;

        /**
        * @brief Create DisplayMode.
        *
        * @param[in] device VkPhysicalDevice.
        * @param[in] display VkDisplayKHR.
        * @param[in] info VkDisplayModeCreateInfoKHR.
        */
        void CreateDisplayMode(VkPhysicalDevice device, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR& info);

    private:

        VkPhysicalDevice m_Device = VK_NULL_HANDLE;       // @brief VkPhysicalDevice.
    };
}

#endif