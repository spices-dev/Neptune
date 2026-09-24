/**
* @file RenderPipeline.cpp.
* @brief The RenderPipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "RenderPipeline.h"

namespace Neptune::WebGPU::Unit {

    RenderPipeline::~RenderPipeline()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuRenderPipelineRelease(m_Handle);
    }

    void RenderPipeline::CreateRenderPipeline(WGPUDevice device, const WGPURenderPipelineDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateRenderPipeline(device, &desc);
    }

    void RenderPipeline::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuRenderPipelineSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif