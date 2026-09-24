/**
* @file Texture.cpp.
* @brief The Texture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "Texture.h"

namespace Neptune::WebGPU::Unit {

    Texture::~Texture()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuTextureRelease(m_Handle);
    }

    void Texture::CreateTexture(WGPUDevice device, const WGPUTextureDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateTexture(device, &desc);
    }

    void Texture::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuTextureSetLabel(m_Handle, { name.c_str(), name.size() });
    }
}

#endif