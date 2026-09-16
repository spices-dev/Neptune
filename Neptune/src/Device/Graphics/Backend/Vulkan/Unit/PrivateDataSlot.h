/**
* @file PrivateDataSlot.h.
* @brief The PrivateDataSlot Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::PrivateDataSlot Class.
    * This class defines the Vulkan::Unit::PrivateDataSlot behaves.
    */
    class PrivateDataSlot : public Unit<VkPrivateDataSlot, VkObjectType::VK_OBJECT_TYPE_PRIVATE_DATA_SLOT>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        PrivateDataSlot() = default;

        /**
        * @brief Destructor Function.
        */
        ~PrivateDataSlot() override;

        /**
        * @brief Create PrivateDataSlot.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkPrivateDataSlotCreateInfo.
        */
        void CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif