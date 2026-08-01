/**
* @file DeferredOperation.h.
* @brief The DeferredOperation Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::DeferredOperation Class.
    * This class defines the Vulkan::Unit::DeferredOperation behaves.
    */
    class DeferredOperation : public Unit<VkDeferredOperationKHR, VkObjectType::VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        DeferredOperation() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~DeferredOperation() override;

        /**
        * @brief Create DeferredOperation.
        *
        * @param[in] device VkDevice.
        */
        void CreateDeferredOperation(VkDevice device);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif