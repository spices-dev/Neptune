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

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddExtensions("GL_NV_conservative_raster");
        
        glGetIntegerv(GL_MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV, &m_MaxSubpixelPrecisionBiasBits);
    }

}

#endif