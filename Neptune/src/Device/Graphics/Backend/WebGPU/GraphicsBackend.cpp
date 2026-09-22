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
    }

    GraphicsBackend::~GraphicsBackend() = default;

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateUP<Context>();
        
        m_Context->Registry<IInstance>();
        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<IAdapter>();
        m_Context->Registry<IDevice>();
        
        m_Context->Registry<IQueue>();
        
        m_Context->Registry<IFuture>(MaxFrameInFlight);
        
        m_Context->Registry<ICommandEncoder>(MaxFrameInFlight);
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

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
            case RHI::ERHI::RenderPass:       return std::static_pointer_cast<RHI::RHIRenderPass::Impl>    (CreateSP<RenderPass>           (*m_Context));
            case RHI::ERHI::CmdList:          return std::static_pointer_cast<RHI::RHICmdList::Impl>       (CreateSP<CmdList>              (*m_Context));
			default:                          NEPTUNE_LOG_CORE(E) << "WebGPU do not support RHI: [ " << ToString(e) << " ].";          return nullptr;
		}
	}

    AInfrastructures GraphicsBackend::AccessInfrastructure() const
	{
        NEPTUNE_PROFILE_ZONE

        AContext context;

        context.Registry<ADevice>(m_Context->Get<IDevice>()->Handle());
        context.Registry<ARTVFormat>(WGPUTextureFormat_RGBA8Unorm);
        context.Registry<ADSVFormat>(WGPUTextureFormat_Undefined);
        
        return context.GetInfrastructures();
	}
    
}

#endif