/**
* @file RenderPassDescriptor.cpp.
* @brief The RenderPassDescriptor Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "RenderPassDescriptor.h"

namespace Neptune::Metal::Unit {

    RenderPassDescriptor::~RenderPassDescriptor()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
    void RenderPassDescriptor::CreateRenderPassDescriptor()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = MTL::RenderPassDescriptor::alloc()->init();
    }
    
}

#endif