/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "Device.h"

namespace Neptune::Metal::Unit {

    Device::~Device()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
    void Device::CreateDevice()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = MTL::CreateSystemDefaultDevice();
    }
    
}

#endif