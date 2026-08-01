/**
* @file IndirectCommandsLayout.h.
* @brief The IndirectCommandsLayout Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::IndirectCommandsLayout Class.
    * This class defines the Vulkan::Unit::IndirectCommandsLayout behaves.
    */
    class IndirectCommandsLayout : public Unit<VkIndirectCommandsLayoutEXT, VkObjectType::VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        IndirectCommandsLayout() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~IndirectCommandsLayout() override;

        /**
        * @brief Create IndirectCommandsLayout.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkIndirectCommandsLayoutCreateInfoEXT.
        */
        void CreateIndirectCommandsLayout(VkDevice device, const VkIndirectCommandsLayoutCreateInfoEXT& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif