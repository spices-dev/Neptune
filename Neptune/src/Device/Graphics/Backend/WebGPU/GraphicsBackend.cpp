/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"

namespace Neptune::WebGPU {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(Graphic::EBackend::WebGPU)
    {
        NEPTUNE_PROFILE_ZONE
        
        HandleResultDelegate::SetHandler([](WGPUStatus result){ HandleResult(result); });
        HandleResultDelegate::SetWaitHandler([](WGPUWaitStatus result){ HandleWaitResult(result); });
    }

    GraphicsBackend::~GraphicsBackend() = default;

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateUP<Context>();
        
        m_Context->Registry<IExtensions>();
        m_Context->Registry<IInstance>();
        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<IAdapter>();
        m_Context->Registry<IDevice>();
        
        m_Context->Registry<IQueue>();
        
        m_Context->Registry<IGraphicTimeLine>(MaxFrameInFlight);
        m_Context->Registry<IComputeTimeLine>(MaxFrameInFlight);
        
        m_Context->Registry<IGraphicCommandEncoder>();
        m_Context->Registry<IComputeCommandEncoder>();
        
        m_Context->Registry<IAccessibleInfrastructures>();
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
        
        m_Context->Get<IQueue>()->OnSubmittedWorkDone();
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
            case RHI::ERHI::Buffer:           return CreateUP<Buffer>               (*m_Context);
            case RHI::ERHI::CmdList:          return CreateUP<CmdList>              (*m_Context);
            case RHI::ERHI::CmdList2:         return CreateUP<CmdList2>             (*m_Context);
			default:                          NEPTUNE_LOG_CORE(E) << "WebGPU do not support RHI: [ " << ToString(e) << " ].";          return nullptr;
		}
	}

    Graphic::AInfrastructures GraphicsBackend::AccessInfrastructure() const
	{
        return m_Context->Get<IAccessibleInfrastructures>()->GetContext();
	}
    
}

#endif