/**
* @file PipelineStatisticsQuery.h.
* @brief The PipelineStatisticsQuery Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IPipelineStatisticsQuery = ICapability<class PipelineStatisticsQuery, ECapability::PipelineStatisticsQuery>;
    
    class PipelineStatisticsQuery : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit PipelineStatisticsQuery(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~PipelineStatisticsQuery() override = default;
        
    private:
        
        GLint m_VerticesSubmitted;
        GLint m_PrimitivesSubmitted;
        GLint m_VertexShaderInvocations;
        GLint m_FragmentShaderInvocations;
        GLint m_ComputeShaderInvocations;
        GLint m_ClippingInputPrimitives;
        GLint m_ClippingOutputPrimitives;
    };
}

#endif