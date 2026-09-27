/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"

namespace Neptune::OpenGL {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(Graphic::EBackend::OpenGL)
    {
        NEPTUNE_PROFILE_ZONE

        HandleResultDelegate::SetHandler([&](GLenum result) { HandleResult(result); });
    }

    GraphicsBackend::~GraphicsBackend() = default;

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateUP<Context>();

        m_Context->Registry<IWindowContext>(window ? window->Implement() : WindowImplement::Default, window ? window->NativeWindow() : nullptr);
        m_Context->Registry<IExtensions>();
        m_Context->Registry<IDebugUtilsObject>();

        m_Context->Registry<ITimeLine>(MaxFrameInFlight);
    }

    void GraphicsBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context->UnRegistry();
    }

    Context& GraphicsBackend::GetContext() const
    {
        return *m_Context;
    }

    void GraphicsBackend::Wait() const
    {
        NEPTUNE_PROFILE_ZONE

        glFinish();
    }

    UP<RHI::RHIImplEmpty> GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
			case RHI::ERHI::Capability:       return CreateUP<Capability>           (*m_Context);
            case RHI::ERHI::RenderPass:       return CreateUP<RenderPass>           (*m_Context);
			case RHI::ERHI::DescriptorList:   return CreateUP<DescriptorList>       (*m_Context);
			case RHI::ERHI::Pipeline:         return CreateUP<Pipeline>             (*m_Context);
			case RHI::ERHI::Shader:           return CreateUP<Shader>               (*m_Context);
			case RHI::ERHI::RenderTarget:     return CreateUP<RenderTarget>         (*m_Context);
			case RHI::ERHI::VertexBuffer:     return CreateUP<VertexBuffer>         (*m_Context);
			case RHI::ERHI::IndexBuffer:      return CreateUP<IndexBuffer>          (*m_Context);
            case RHI::ERHI::CmdList:          return CreateUP<CmdList>              (*m_Context);
			case RHI::ERHI::CmdList2:         return CreateUP<CmdList2>             (*m_Context);
            case RHI::ERHI::Decoder:          NEPTUNE_LOG_CORE(E) << "OpenGL do not support RHI: [ " << ToString(e) << " ].";   return nullptr;
            case RHI::ERHI::OpticalFlow:      NEPTUNE_LOG_CORE(E) << "OpenGL do not support RHI: [ " << ToString(e) << " ].";   return nullptr;
			default:                          NEPTUNE_LOG_CORE(E) << "OpenGL do not support RHI: [ " << ToString(e) << " ].";   return nullptr;
		}
	}

    AInfrastructures GraphicsBackend::AccessInfrastructure() const
	{
        NEPTUNE_PROFILE_ZONE

    	AContext context;

    	context.Registry<AApiVersionName>(m_Context->Get<IExtensions>()->GetApiVersionName());
    	
		return context.GetInfrastructures();
	}
}

#endif