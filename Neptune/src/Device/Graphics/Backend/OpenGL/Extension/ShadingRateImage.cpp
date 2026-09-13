/**
* @file ShadingRateImage.cpp.
* @brief The ShadingRateImage Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShadingRateImage.h"

namespace Neptune::OpenGL::Extension {

    ShadingRateImage::ShadingRateImage(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_NV_shading_rate_image");
    }

    void ShadingRateImage::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_SHADING_RATE_IMAGE_TEXEL_WIDTH_NV, &m_TexelWidth);
        glGetIntegerv(GL_SHADING_RATE_IMAGE_TEXEL_HEIGHT_NV, &m_TexelHeight);
        glGetIntegerv(GL_SHADING_RATE_IMAGE_PALETTE_SIZE_NV, &m_PaletteSize);
    }
    
    bool ShadingRateImage::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "ShadingRateImage [ texelWidth ] : " << m_TexelWidth;
        NEPTUNE_LOG_CORE(I) << "ShadingRateImage [ texelHeight ] : " << m_TexelHeight;
        NEPTUNE_LOG_CORE(I) << "ShadingRateImage [ paletteSize ] : " << m_PaletteSize;

        return true;
    }
    
}

#endif