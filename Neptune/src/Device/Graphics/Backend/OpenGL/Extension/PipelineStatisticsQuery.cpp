/**
* @file PipelineStatisticsQuery.cpp.
* @brief The PipelineStatisticsQuery Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "PipelineStatisticsQuery.h"

namespace Neptune::OpenGL::Extension {

    PipelineStatisticsQuery::PipelineStatisticsQuery(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;
        
        AddExtensions("GL_ARB_pipeline_statistics_query");
    }
    
    void PipelineStatisticsQuery::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetQueryiv(GL_VERTICES_SUBMITTED, GL_QUERY_COUNTER_BITS, &m_VerticesSubmitted);
        glGetQueryiv(GL_PRIMITIVES_SUBMITTED, GL_QUERY_COUNTER_BITS, &m_PrimitivesSubmitted);
        glGetQueryiv(GL_VERTEX_SHADER_INVOCATIONS, GL_QUERY_COUNTER_BITS, &m_VertexShaderInvocations);
        glGetQueryiv(GL_FRAGMENT_SHADER_INVOCATIONS, GL_QUERY_COUNTER_BITS, &m_FragmentShaderInvocations);
        glGetQueryiv(GL_COMPUTE_SHADER_INVOCATIONS, GL_QUERY_COUNTER_BITS, &m_ComputeShaderInvocations);
        glGetQueryiv(GL_CLIPPING_INPUT_PRIMITIVES, GL_QUERY_COUNTER_BITS, &m_ClippingInputPrimitives);
        glGetQueryiv(GL_CLIPPING_OUTPUT_PRIMITIVES, GL_QUERY_COUNTER_BITS, &m_ClippingOutputPrimitives);
    }
    
    bool PipelineStatisticsQuery::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "PipelineStatisticsQuery [ verticesSubmitted ] : " << m_VerticesSubmitted;
        NEPTUNE_LOG_CORE(I) << "PipelineStatisticsQuery [ primitivesSubmitted ] : " << m_PrimitivesSubmitted;
        NEPTUNE_LOG_CORE(I) << "PipelineStatisticsQuery [ vertexShaderInvocations ] : " << m_VertexShaderInvocations;
        NEPTUNE_LOG_CORE(I) << "PipelineStatisticsQuery [ fragmentShaderInvocations ] : " << m_FragmentShaderInvocations;
        NEPTUNE_LOG_CORE(I) << "PipelineStatisticsQuery [ computeShaderInvocations ] : " << m_ComputeShaderInvocations;
        NEPTUNE_LOG_CORE(I) << "PipelineStatisticsQuery [ clippingInputPrimitives ] : " << m_ClippingInputPrimitives;
        NEPTUNE_LOG_CORE(I) << "PipelineStatisticsQuery [ clippingOutputPrimitives ] : " << m_ClippingOutputPrimitives;

        return true;
    }

}

#endif