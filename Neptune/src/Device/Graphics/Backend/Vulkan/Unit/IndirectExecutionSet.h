/**
* @file IndirectExecutionSet.h.
* @brief The IndirectExecutionSet Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::IndirectExecutionSet Class.
    * This class defines the Vulkan::Unit::IndirectExecutionSet behaves.
    */
    class IndirectExecutionSet : public Unit<VkIndirectExecutionSetEXT, VkObjectType::VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        IndirectExecutionSet() = default;

        /**
        * @brief Destructor Function.
        */
        ~IndirectExecutionSet() override;

        /**
        * @brief Create IndirectExecutionSet.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkIndirectExecutionSetCreateInfoEXT.
        */
        void CreateIndirectExecutionSet(VkDevice device, const VkIndirectExecutionSetCreateInfoEXT& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif