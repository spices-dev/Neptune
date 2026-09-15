/**
* @file MeshShader.cpp.
* @brief The MeshShader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "MeshShader.h"

namespace Neptune::Vulkan::Extension {
    
    MeshShader::MeshShader(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_EXT_MESH_SHADER_EXTENSION_NAME);
    }
    
}

#endif