/**
* @file ShaderModule.h.
* @brief The ShaderModule Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::ShaderModule Class.
    * This class defines the Vulkan::Unit::ShaderModule behaves.
    */
    class ShaderModule : public Unit<VkShaderModule, VkObjectType::VK_OBJECT_TYPE_SHADER_MODULE>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ShaderModule() = default;

        /**
        * @brief Destructor Function.
        */
        ~ShaderModule() override;

        /**
        * @brief Create ShaderModule.
        *
        * @param[in] device VkDevice.
        * @param[in] info VkShaderModuleCreateInfo.
        */
        void CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo& info);

    private:

        VkDevice m_Device = VK_NULL_HANDLE;         // @brief VkDevice.
    };
}

#endif