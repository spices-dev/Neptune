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

        //if constexpr (IsCoreCapability<decltype(*this)>) return;
        
        AddExtensions("GL_ARB_pipeline_statistics_query");
        
        glGetQueryiv(GL_VERTICES_SUBMITTED, GL_QUERY_COUNTER_BITS, &m_VerticesSubmitted);
        glGetQueryiv(GL_PRIMITIVES_SUBMITTED, GL_QUERY_COUNTER_BITS, &m_PrimitivesSubmitted);
        glGetQueryiv(GL_VERTEX_SHADER_INVOCATIONS, GL_QUERY_COUNTER_BITS, &m_VertexShaderInvocations);
        glGetQueryiv(GL_FRAGMENT_SHADER_INVOCATIONS, GL_QUERY_COUNTER_BITS, &m_FragmentShaderInvocations);
        glGetQueryiv(GL_COMPUTE_SHADER_INVOCATIONS, GL_QUERY_COUNTER_BITS, &m_ComputeShaderInvocations);
        glGetQueryiv(GL_CLIPPING_INPUT_PRIMITIVES, GL_QUERY_COUNTER_BITS, &m_ClippingInputPrimitives);
        glGetQueryiv(GL_CLIPPING_OUTPUT_PRIMITIVES, GL_QUERY_COUNTER_BITS, &m_ClippingOutputPrimitives);
    }

}

#endif