/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGL

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::WebGL {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(Graphic::EBackend::WebGL)
    {
        NEPTUNE_PROFILE_ZONE
    }

    GraphicsBackend::~GraphicsBackend() = default;

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateUP<Context>();
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

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
			default:                          NEPTUNE_LOG_CORE(E) << "WebGL do not support RHI: [ " << ToString(e) << " ].";          return nullptr;
		}
	}

    AInfrastructures GraphicsBackend::AccessInfrastructure() const
	{
        NEPTUNE_PROFILE_ZONE

        AContext context;

		return context.GetInfrastructures();
	}
}

#endif