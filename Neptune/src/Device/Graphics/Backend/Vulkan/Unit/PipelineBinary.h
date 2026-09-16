/**
* @file PipelineBinary.h.
* @brief The PipelineBinary Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::PipelineBinary Class.
    * This class defines the Vulkan::Unit::PipelineBinary behaves.
    */
    class PipelineBinary : public Unit<VkPipelineBinaryKHR, VkObjectType::VK_OBJECT_TYPE_PIPELINE_BINARY_KHR>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        PipelineBinary() = default;

        /**
        * @brief Destructor Function.
        */
        ~PipelineBinary() override;

        /**
        * @brief Create PipelineBinary.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkPipelineBinaryCreateInfoKHR.
        */
        void CreatePipelineBinary(VkDevice device, const VkPipelineBinaryCreateInfoKHR& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
    };
}

#endif