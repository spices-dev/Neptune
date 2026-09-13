/**
* @file PipelineStatisticsQuery.h.
* @brief The PipelineStatisticsQuery Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IPipelineStatisticsQuery = IExtension<class PipelineStatisticsQuery, EExtension::PipelineStatisticsQuery>;
    
    class PipelineStatisticsQuery : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit PipelineStatisticsQuery(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~PipelineStatisticsQuery() override = default;
        
        /**
        * @brief Query Extension Properties.
        */
        void QueryProperties() override;
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;
        
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