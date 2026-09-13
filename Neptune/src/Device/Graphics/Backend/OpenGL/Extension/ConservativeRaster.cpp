/**
* @file ConservativeRaster.cpp.
* @brief The ConservativeRaster Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ConservativeRaster.h"

namespace Neptune::OpenGL::Extension {

    ConservativeRaster::ConservativeRaster(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_NV_conservative_raster");
    }

    void ConservativeRaster::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV, &m_MaxSubpixelPrecisionBiasBits);
    }
    
    bool ConservativeRaster::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "ConservativeRaster [ maxSubpixelPrecisionBiasBits ] : " << m_MaxSubpixelPrecisionBiasBits;

        return true;
    }
    
}

#endif