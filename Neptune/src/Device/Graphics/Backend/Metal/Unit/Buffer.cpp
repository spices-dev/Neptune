/**
* @file Buffer.cpp.
* @brief The Buffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "Buffer.h"

namespace Neptune::Metal::Unit {

    Buffer::~Buffer()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
}

#endif