/**
* @file DescriptorHeap.cpp.
* @brief The DescriptorHeap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DescriptorHeap.h"

namespace Neptune::Vulkan::Extension {
    
    DescriptorHeap::DescriptorHeap(EExtensionState state)
        : Extension(state)
    {}
    
}

#endif