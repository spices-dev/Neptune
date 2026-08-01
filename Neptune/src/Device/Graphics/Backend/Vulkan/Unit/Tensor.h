/**
* @file Tensor.h.
* @brief The Tensor Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::Tensor Class.
    * This class defines the Vulkan::Unit::Tensor behaves.
    */
    class Tensor : public Unit<VkTensorARM, VkObjectType::VK_OBJECT_TYPE_TENSOR_ARM>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Tensor() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~Tensor() override;

        /**
        * @brief Create Tensor.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkTensorCreateInfoARM.
        */
        void CreateTensor(VkDevice device, const VkTensorCreateInfoARM& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif