/**
* @file DebugUtils.cpp.
* @brief The DebugUtils Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DebugUtils.h"

namespace Neptune::Vulkan::Extension {
    
    DebugUtils::DebugUtils(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        AddInstanceExtensions(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        
#if 0

        m_Features.push_back(VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT);
	
#if 0

        m_Features.push_back(VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT);
        m_Features.push_back(VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT);
        m_Features.push_back(VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT);
        m_Features.push_back(VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT);

#endif
        
#endif
        
    }
    
}

#endif