/**
* @file RenderPipelineState.cpp.
* @brief The RenderPipelineState Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "RenderPipelineState.h"

namespace Neptune::Metal::Unit {

    RenderPipelineState::~RenderPipelineState()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->release();
    }
    
}

#endif