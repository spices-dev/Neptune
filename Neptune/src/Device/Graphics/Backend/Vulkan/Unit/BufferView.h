/**
* @file BufferView.h.
* @brief The BufferView Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::BufferView Class.
    * This class defines the Vulkan::Unit::BufferView behaves.
    */
    class BufferView : public Unit<VkBufferView, VkObjectType::VK_OBJECT_TYPE_BUFFER_VIEW>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        BufferView() = default;

        /**
        * @brief Destructor Function.
        */
        ~BufferView() override;

        /**
        * @brief Create BufferView.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkBufferViewCreateInfo.
        */
        void CreateBufferView(VkDevice device, const VkBufferViewCreateInfo& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif