/**
* @file TensorView.h.
* @brief The TensorView Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::TensorView Class.
    * This class defines the Vulkan::Unit::TensorView behaves.
    */
    class TensorView : public Unit<VkTensorViewARM, VkObjectType::VK_OBJECT_TYPE_TENSOR_VIEW_ARM>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        TensorView() = default;

        /**
        * @brief Destructor Function.
        */
        ~TensorView() override;

        /**
        * @brief Create TensorView.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkTensorViewCreateInfoARM.
        */
        void CreateTensorView(VkDevice device, const VkTensorViewCreateInfoARM& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif