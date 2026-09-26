/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "RenderBackend.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/InfrastructureHeader.h"
#include "Device/Graphics/Backend/WebGPU/AInfrastructure/AccessibleInfrastructure.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::WebGPU {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::WebGPU)
        , m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        const auto& window = Window::Instance();
        
        m_GraphicsBackend->OnInitialize(&window);
        
        GetContext().Registry<ISurface>(window.Extent());

        RenderFrontend::OnInitialize();
    }

    void RenderBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        RenderFrontend::OnShutDown();

        m_GraphicsBackend->OnShutDown();
    }

    void RenderBackend::BeginFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE

        auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

        auto& context = m_GraphicsBackend->GetContext();
        
        if (clock.m_FrameId > MaxFrameInFlight)
        {
            context.Get<IComputeTimeLine>()->Wait(clock.m_FrameId - MaxFrameInFlight);
            
            context.Get<IGraphicTimeLine>()->Wait(clock.m_FrameId - MaxFrameInFlight);
        }

        {
            if (!context.Get<ISurface>()->GetNextImage())
            {
                NEPTUNE_LOG_CORE(E) << "GetNextImage Failed.";
                
                NEPTUNE_BREAK
            }
        }

        {
            context.Get<IComputeCommandEncoder>()->Begin();
            
            context.Get<IGraphicCommandEncoder>()->Begin();
        }
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

        auto& context = m_GraphicsBackend->GetContext();
        
		{
			DEBUGUTILS_BEGINLABEL(context.Get<IQueue>()->Handle(), "MainComputeQueue")

			context.Get<IComputeTimeLine>()->SetHandle(clock.m_FrameId, context.Get<IQueue>()->Submit(context.Get<IComputeCommandEncoder>()->End()));

			DEBUGUTILS_ENDLABEL(context.Get<IQueue>()->Handle())
		}
        
        {
            DEBUGUTILS_BEGINLABEL(context.Get<IQueue>()->Handle(), "MainGraphicQueue")

            context.Get<IGraphicTimeLine>()->SetHandle(clock.m_FrameId, context.Get<IQueue>()->Submit(context.Get<IGraphicCommandEncoder>()->End()));

            DEBUGUTILS_ENDLABEL(context.Get<IQueue>()->Handle())
        }
        
        {
#if WEBGPU_USE_NATIVE
            
            if (!context.Get<ISurface>()->Present())
            {
                NEPTUNE_LOG_CORE(E) << "Present Failed.";
                
                NEPTUNE_BREAK
            }
            
#endif
        }
    }

    void RenderBackend::Wait() const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_GraphicsBackend->Wait();
    }

    GraphicsBackend::Context& RenderBackend::GetContext() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_GraphicsBackend->GetContext();
    }
    
    UP<RHI::RHIImplEmpty> RenderBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        return m_GraphicsBackend->CreateRHI(e, payload);
	}

    AInfrastructures RenderBackend::AccessInfrastructure() const
	{
        NEPTUNE_PROFILE_ZONE
        
		return m_GraphicsBackend->AccessInfrastructure();
	}
}

#endif