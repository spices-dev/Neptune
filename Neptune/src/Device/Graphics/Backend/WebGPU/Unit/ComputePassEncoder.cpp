/**
* @file ComputePassEncoder.cpp.
* @brief The ComputePassEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "ComputePassEncoder.h"

namespace Neptune::WebGPU::Unit {

    ComputePassEncoder::~ComputePassEncoder()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuComputePassEncoderRelease(m_Handle);
    }

    void ComputePassEncoder::CreateComputePassEncoder(WGPUCommandEncoder commandEncoder, const WGPUComputePassDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuCommandEncoderBeginComputePass(commandEncoder, &desc);
    }

    void ComputePassEncoder::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuComputePassEncoderSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif