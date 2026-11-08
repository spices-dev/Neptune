/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::Buffer Class.
    * This class defines the Vulkan::Unit::Buffer behaves.
    */
    class Buffer : public Unit<VkBuffer, PFN_vkCreateBuffer, PFN_vkDestroyBuffer>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Buffer() = default;

        /**
        * @brief Destructor Function.
        */
        ~Buffer() override;

        /**
        * @brief Create Buffer.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkBufferCreateInfo.
        * 
        * @return Returns VkResult.
        */
        VkResult CreateBuffer(VkDevice device, const VkBufferCreateInfo& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;     // @brief VkDevice.

    };
}