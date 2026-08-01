/**
* @file DescriptorUpdateTemplate.h.
* @brief The DescriptorUpdateTemplate Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::DescriptorUpdateTemplate Class.
    * This class defines the Vulkan::Unit::DescriptorUpdateTemplate behaves.
    */
    class DescriptorUpdateTemplate : public Unit<VkDescriptorUpdateTemplate, VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        DescriptorUpdateTemplate() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~DescriptorUpdateTemplate() override;

        /**
        * @brief Create DescriptorUpdateTemplate.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkDescriptorUpdateTemplateCreateInfo.
        */
        void CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif