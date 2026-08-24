/**
* @file ShaderInstrumentation.h.
* @brief The ShaderInstrumentation Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::ShaderInstrumentation Class.
    * This class defines the Vulkan::Unit::ShaderInstrumentation behaves.
    */
    class ShaderInstrumentation : public Unit<VkShaderInstrumentationARM, VkObjectType::VK_OBJECT_TYPE_SHADER_INSTRUMENTATION_ARM>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ShaderInstrumentation() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~ShaderInstrumentation() override;

        /**
        * @brief Create CreateShaderInstrumentation.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkShaderInstrumentationCreateInfoARM.
        */
        void CreateShaderInstrumentation(VkDevice device, const VkShaderInstrumentationCreateInfoARM& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;         // @brief VkDevice.
    };
}

#endif