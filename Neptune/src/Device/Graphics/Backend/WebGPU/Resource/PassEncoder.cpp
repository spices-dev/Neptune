/**
* @file PassEncoder.cpp.
* @brief The PassEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "PassEncoder.h"
#include "Device/Graphics/Backend/WebGPU/RHI/Pipeline.h"

namespace Neptune::WebGPU::Resource {

    void PassEncoder::EndPass() const
    {
        NEPTUNE_PROFILE_ZONE
        
        if (m_RenderBindPoint)
        {
            IHandle<Unit::RenderPassEncoder>()->EndRenderPass();
        }
        else
        {
            IHandle<Unit::ComputePassEncoder>()->EndComputePass();
        }
    }
    
    void PassEncoder::BindPipeline(const WebGPU::Pipeline* pipeline) const
    {
        NEPTUNE_PROFILE_ZONE
        
        if (m_RenderBindPoint)
        {
            IHandle<Unit::RenderPassEncoder>()->SetPipeline(pipeline->Handle<Unit::RenderPipeline>());
        }
        else
        {
            IHandle<Unit::ComputePassEncoder>()->SetPipeline(pipeline->Handle<Unit::ComputePipeline>());
        }
    }
    
}

#endif