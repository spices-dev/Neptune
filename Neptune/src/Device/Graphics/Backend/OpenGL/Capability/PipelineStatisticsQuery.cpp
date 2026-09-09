/**
* @file PipelineStatisticsQuery.cpp.
* @brief The PipelineStatisticsQuery Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "PipelineStatisticsQuery.h"

namespace Neptune::OpenGL::Capability {

    PipelineStatisticsQuery::PipelineStatisticsQuery(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_ARB_pipeline_statistics_query");
        
        // TODO
    }

}

#endif