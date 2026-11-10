/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"

namespace Neptune::Metal {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(Graphic::EBackend::Metal)
    {
        NEPTUNE_PROFILE_ZONE
        
        HandleResultDelegate::SetHandler([&](const NS::Error* result) { HandleResult(result); });
    }

    GraphicsBackend::~GraphicsBackend() = default;

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateUP<Context>();
        
        m_Context->Registry<IFrameAutoreleasePool>();
        m_Context->Registry<IDevice>();
        m_Context->Registry<ILayer>(MaxFrameInFlight);
        m_Context->Registry<ICommandQueue>();
        m_Context->Registry<ICommandBuffer>();
        m_Context->Registry<IGraphicDispatchSemaphore>(MaxFrameInFlight);
        
        m_Context->Registry<IGarbageCollection>();
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
    }

    UP<RHI::RHIImplEmpty> GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        return nullptr;
	}
    
    Graphic::AInfrastructures GraphicsBackend::AccessInfrastructure() const
    {
        return m_Context->Get<IAccessibleInfrastructures>()->GetContext();
    }
    
}

#endif