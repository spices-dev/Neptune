/**
* @file ComputePipeline.cpp.
* @brief The ComputePipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "ComputePipeline.h"

namespace Neptune::WebGPU::Unit {

    ComputePipeline::~ComputePipeline()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuComputePipelineRelease(m_Handle);
    }

    void ComputePipeline::CreateComputePipeline(WGPUDevice device, const WGPUComputePipelineDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateComputePipeline(device, &desc);
    }

    void ComputePipeline::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuComputePipelineSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif