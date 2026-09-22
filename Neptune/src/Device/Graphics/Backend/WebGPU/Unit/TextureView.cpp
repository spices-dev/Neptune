/**
* @file TextureView.cpp.
* @brief The TextureView Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "TextureView.h"

namespace Neptune::WebGPU::Unit {

    TextureView::~TextureView()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuTextureViewRelease(m_Handle);
    }

    void TextureView::CreateTextureView(WGPUTexture texture, const WGPUTextureViewDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuTextureCreateView(texture, &desc);
    }
	
    void TextureView::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuTextureViewSetLabel(m_Handle, { name.c_str(), name.size() });
    }
}

#endif