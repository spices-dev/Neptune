/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "RenderBackend.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/InfrastructureHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::OpenGL {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::OpenGL)
        , m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        const auto& window = Window::Instance();

        m_GraphicsBackend->OnInitialize(&window);
        
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
        
        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

        auto& context = m_GraphicsBackend->GetContext();
        
        context.Get<IGarbageCollection>()->SetFrameId(clock.m_FrameId);
        
        if (clock.m_FrameId > MaxFrameInFlight)
        {
            context.Get<ITimeLine>()->Wait(clock.m_FrameId - MaxFrameInFlight);
            
            context.Get<IGarbageCollection>()->Flush(clock.m_FrameId - MaxFrameInFlight);
        }

        {
            DEBUGUTILS_BEGINLABEL(0, "MainQueue")
        }
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();
        
        auto& context = m_GraphicsBackend->GetContext();
        
        {
            DEBUGUTILS_ENDLABEL()
        }

        {
            DEBUGUTILS_BEGINLABEL(0, "PresentQueue")
            
            context.Get<IWindowContext>()->SwapBuffers();

            DEBUGUTILS_ENDLABEL()
        }
        
        {
            context.Get<ITimeLine>()->Signal(clock.m_FrameId);
        }
    }

    void RenderBackend::Wait() const
    {
        m_GraphicsBackend->Wait();
    }

    GraphicsBackend::Context& RenderBackend::GetContext() const
    {
        return m_GraphicsBackend->GetContext();
    }
    
    UP<RHI::RHIImplEmpty> RenderBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        return m_GraphicsBackend->CreateRHI(e, payload);
	}

    Graphic::AInfrastructures RenderBackend::AccessInfrastructure() const
	{
		return m_GraphicsBackend->AccessInfrastructure();
	}
    
}

#endif