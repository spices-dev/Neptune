/**
* @file CreateRenderPass2.cpp.
* @brief The CreateRenderPass2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CreateRenderPass2.h"

namespace Neptune::Vulkan::Extension {

    CreateRenderPass2::CreateRenderPass2(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME);
    }

}

#endif