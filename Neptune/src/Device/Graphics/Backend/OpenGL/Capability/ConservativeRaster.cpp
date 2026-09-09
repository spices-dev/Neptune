/**
* @file ConservativeRaster.cpp.
* @brief The ConservativeRaster Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ConservativeRaster.h"

namespace Neptune::OpenGL::Capability {

    ConservativeRaster::ConservativeRaster(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_NV_conservative_raster");
        
        glGetIntegerv(GL_MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV, &m_MaxSubpixelPrecisionBiasBits);
    }

}

#endif