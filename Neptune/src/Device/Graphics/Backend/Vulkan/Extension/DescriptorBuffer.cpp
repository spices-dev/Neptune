/**
* @file DescriptorBuffer.cpp.
* @brief The DescriptorBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DescriptorBuffer.h"

namespace Neptune::Vulkan::Extension {
    
    DescriptorBuffer::DescriptorBuffer(EExtensionState state)
        : Extension(state)
    {}
    
}

#endif