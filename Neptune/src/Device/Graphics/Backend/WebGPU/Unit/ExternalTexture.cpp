/**
* @file ExternalTexture.cpp.
* @brief The ExternalTexture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "ExternalTexture.h"

namespace Neptune::WebGPU::Unit {

    ExternalTexture::~ExternalTexture()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuExternalTextureRelease(m_Handle);
    }

    void ExternalTexture::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuExternalTextureSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif