/**
* @file Semaphore.h.
* @brief The Semaphore Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::Semaphore Class.
    * This class defines the Vulkan::Unit::Semaphore behaves.
    */
    class Semaphore : public Unit<VkSemaphore, PFN_vkCreateSemaphore, PFN_vkDestroySemaphore>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Semaphore() = default;

        /**
        * @brief Destructor Function.
        */
        ~Semaphore() override;

        /**
        * @brief Create Semaphore.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkSemaphoreCreateInfo.
        * 
        * @return Returns VkResult.
        */
        VkResult CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;     // @brief VkDevice.

    };
}