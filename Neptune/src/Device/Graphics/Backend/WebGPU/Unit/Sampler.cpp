/**
* @file Sampler.cpp.
* @brief The Sampler Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "Sampler.h"

namespace Neptune::WebGPU::Unit {

    Sampler::~Sampler()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuSamplerRelease(m_Handle);
    }

    void Sampler::CreateSampler(WGPUDevice device, const WGPUSamplerDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateSampler(device, &desc);
    }

    void Sampler::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuSamplerSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif