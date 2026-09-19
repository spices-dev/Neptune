/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGLES

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "AInfrastructure/AccessibleInfrastructure.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"

namespace Neptune::OpenGLES {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(Graphic::EBackend::OpenGLES)
    {
        NEPTUNE_PROFILE_ZONE

        HandleResultDelegate::SetHandler([&](GLenum result) { HandleResult(result); });
    }

    GraphicsBackend::~GraphicsBackend() = default;

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateUP<Context>();

        //m_Context->Registry<IWindowContext>(window ? window->Implement() : WindowImplement::Default, window ? window->NativeWindow() : nullptr);
        //m_Context->Registry<IDebugUtilsObject>();

        //m_Context->Registry<IGraphicFence>(MaxFrameInFlight);
    }

    void GraphicsBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        //m_Context->UnRegistry();
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

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
			default:                          NEPTUNE_LOG_CORE(E) << "OpenGLES do not support RHI: [ " << ToString(e) << " ].";          return nullptr;
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