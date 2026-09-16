/**
* @file Event.h.
* @brief The Event Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::Event Class.
    * This class defines the Vulkan::Unit::Event behaves.
    */
    class Event : public Unit<VkEvent, VkObjectType::VK_OBJECT_TYPE_EVENT>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Event() = default;

        /**
        * @brief Destructor Function.
        */
        ~Event() override;

        /**
        * @brief Create Event.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkEventCreateInfo.
        */
        void CreateEvent(VkDevice device, const VkEventCreateInfo& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif