/**
* @file Display.cpp.
* @brief The Display Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Display.h"

namespace Neptune::Vulkan::Unit {

    Display::~Display()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        VULKAN_CHECK(vkReleaseDisplayEXT(m_Device, m_Handle))
    }
    
}

#endif