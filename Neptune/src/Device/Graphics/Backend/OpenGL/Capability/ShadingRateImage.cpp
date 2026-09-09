/**
* @file ShadingRateImage.cpp.
* @brief The ShadingRateImage Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShadingRateImage.h"

namespace Neptune::OpenGL::Capability {

    ShadingRateImage::ShadingRateImage(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_NV_shading_rate_image");
        
        glGetIntegerv(GL_SHADING_RATE_IMAGE_TEXEL_WIDTH_NV, &m_TexelWidth);
        glGetIntegerv(GL_SHADING_RATE_IMAGE_TEXEL_HEIGHT_NV, &m_TexelHeight);
        glGetIntegerv(GL_SHADING_RATE_IMAGE_PALETTE_SIZE_NV, &m_PaletteSize);
    }

}

#endif