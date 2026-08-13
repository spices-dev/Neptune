/**
* @file RenderPipelineDescriptor.cpp.
* @brief The RenderPipelineDescriptor Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "RenderPipelineDescriptor.h"

namespace Neptune::Metal::Unit {

    RenderPipelineDescriptor::~RenderPipelineDescriptor()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
    void RenderPipelineDescriptor::CreateRenderPipelineDescriptor()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Handle = MTL::RenderPipelineDescriptor::alloc()->init();
    }
    
}

#endif