/**
* @file MemoryBudget.cpp.
* @brief The MemoryBudget Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "MemoryBudget.h"

namespace Neptune::Vulkan::Extension {
    
    MemoryBudget::MemoryBudget(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME);
    }
    
}

#endif