/**
* @file GpaSession.h.
* @brief The GpaSession Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::GpaSession Class.
    * This class defines the Vulkan::Unit::GpaSession behaves.
    */
    class GpaSession : public Unit<VkGpaSessionAMD, VkObjectType::VK_OBJECT_TYPE_GPA_SESSION_AMD>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        GpaSession() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~GpaSession() override;

        /**
        * @brief Create GpaSession.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkGpaSessionCreateInfoAMD.
        */
        void CreateGpaSession(VkDevice device, const VkGpaSessionCreateInfoAMD& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;          // @brief VkDevice
    };
}

#endif