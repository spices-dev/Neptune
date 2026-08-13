/**
* @file Function.cpp.
* @brief The Function Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "Function.h"

namespace Neptune::Metal::Unit {

    Function::~Function()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
}

#endif