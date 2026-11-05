/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "RenderBackend.h"
#include "Device/Graphics/Backend/Metal/Infrastructure/InfrastructureHeader.h"
#include "Device/Graphics/Backend/Metal/AInfrastructure/AccessibleInfrastructure.h"
#include "Device/Graphics/Backend/Metal/RHI/RenderPass.h"
#include "Render/Frontend/Pass/SlatePass.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::Metal {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::Metal)
        , m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_GraphicsBackend->OnInitialize();
        
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
        
        auto& context = m_GraphicsBackend->GetContext();
        
        context.Get<IFrameAutoreleasePool>()->Init();
        
        {
            context.Get<IGraphicDispatchSemaphore>()->Wait();
        }
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE
        
        GetContext().Get<IFrameAutoreleasePool>()->Release();
    }

    void RenderBackend::Wait() const
    {
        NEPTUNE_PROFILE_ZONE
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
    
    std::any RenderBackend::AccessInfrastructure() const
    {
        NEPTUNE_PROFILE_ZONE

        auto context = std::any_cast<AContext>(m_GraphicsBackend->AccessInfrastructure());

        auto pass = std::dynamic_pointer_cast<Render::SlatePass>(m_RenderPasses.back());
        
        auto desc = pass->GetRenderPass()->GetRHIImpl<RenderPass>()->GetDescriptor();
        
        context.Registry<ARenderPassDescriptor>(*desc);
    	
        return context;
    }
}

#endif