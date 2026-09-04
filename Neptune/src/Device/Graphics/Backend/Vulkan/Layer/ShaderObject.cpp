/**
* @file ShaderObject.cpp.
* @brief The ShaderObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ShaderObject.h"

namespace Neptune::Vulkan::Layer {

    ShaderObject::ShaderObject(ELayerState state)
        : Layer("VK_LAYER_KHRONOS_shader_object", state)
    {
        NEPTUNE_PROFILE_ZONE

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("force_enable", data);
        }

        {
            static constexpr VkBool32 data = VK_FALSE;

            AddLayerSetting("disable_pipeline_pre_caching", data);
        }
    }

}

#endif