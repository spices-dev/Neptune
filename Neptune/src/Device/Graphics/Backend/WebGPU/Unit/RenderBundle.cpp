/**
* @file RenderBundle.cpp.
* @brief The RenderBundle Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "RenderBundle.h"

namespace Neptune::WebGPU::Unit {

    RenderBundle::~RenderBundle()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuRenderBundleRelease(m_Handle);
    }

    void RenderBundle::CreateRenderBundle(WGPURenderBundleEncoder renderBundleEncoder, const WGPURenderBundleDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuRenderBundleEncoderFinish(renderBundleEncoder, &desc);
    }

    void RenderBundle::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuRenderBundleSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif