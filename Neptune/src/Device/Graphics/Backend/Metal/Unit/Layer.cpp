/**
* @file Layer.cpp.
* @brief The Layer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "Layer.h"

namespace Neptune::Metal::Unit {

    Layer::~Layer()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
    void Layer::CreateLayer()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = CA::MetalLayer::layer()->retain();
    }
}

#endif