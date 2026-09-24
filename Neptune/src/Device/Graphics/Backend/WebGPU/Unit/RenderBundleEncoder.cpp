/**
* @file RenderBundleEncoder.cpp.
* @brief The RenderBundleEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "RenderBundleEncoder.h"

namespace Neptune::WebGPU::Unit {

    RenderBundleEncoder::~RenderBundleEncoder()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuRenderBundleEncoderRelease(m_Handle);
    }

    void RenderBundleEncoder::CreateRenderBundleEncoder(WGPUDevice device, const WGPURenderBundleEncoderDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateRenderBundleEncoder(device, &desc);
    }

    void RenderBundleEncoder::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuRenderBundleEncoderSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif