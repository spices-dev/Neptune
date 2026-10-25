/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RenderBackend.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/InfrastructureHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::Direct3D12 {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::Direct3D12)
		, m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

    	m_GraphicsBackend->OnInitialize();
    	
        const auto& window = Window::Instance();

    	GetContext().Registry<ISwapChain>(SwapChainImageCount, window.Implement(), window.NativeWindow());
    	
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
            context.Get<IComputeCommandList>()->Begin(clock.m_FrameId);

            context.Get<IGraphicCommandList>()->Begin(clock.m_FrameId);
		}
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

    	auto& context = m_GraphicsBackend->GetContext();
    	
		{
			context.Get<IComputeCommandList>()->End(clock.m_FrameId);

			context.Get<IGraphicCommandList>()->End(clock.m_FrameId);
		}

		{
            DEBUGUTILS_BEGINQUEUELABEL(context.Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			context.Get<IComputeQueue>()->Submit(context.Get<IComputeCommandList>()->Handle(clock.m_FrameId), context.Get<IComputeTimeLine>()->IHandle(clock.m_FrameId));
        	
			DEBUGUTILS_ENDQUEUELABEL(context.Get<IComputeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			context.Get<IGraphicQueue>()->Submit(context.Get<IGraphicCommandList>()->Handle(clock.m_FrameId), context.Get<IGraphicTimeLine>()->IHandle(clock.m_FrameId));
        	
			DEBUGUTILS_ENDQUEUELABEL(context.Get<IGraphicQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			context.Get<ISwapChain>()->Present();

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IGraphicQueue>()->Handle())
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