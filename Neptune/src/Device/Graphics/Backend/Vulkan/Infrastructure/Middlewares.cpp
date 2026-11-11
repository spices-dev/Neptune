/**
* @file Middlewares.cpp.
* @brief The Middlewares Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Middlewares.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/MiddlewareHeader.h"

namespace Neptune::Vulkan {

    Middlewares::Middlewares(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void Middlewares::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Context = CreateSP<Middleware::MContext<EMiddleware>>();

        m_Context->Registry<Middleware::IIGetPhysicalDeviceProperties> (Infrastructure::GetContext());
        m_Context->Registry<Middleware::IIGetSurfaceCapabilities>      (Infrastructure::GetContext());
        m_Context->Registry<Middleware::IIImageLayout>                 (Infrastructure::GetContext());
        m_Context->Registry<Middleware::IIIndirect>                    (Infrastructure::GetContext());
        m_Context->Registry<Middleware::IIQueueSubmit>                 (Infrastructure::GetContext());
        m_Context->Registry<Middleware::IISynchronization>             (Infrastructure::GetContext());
        m_Context->Registry<Middleware::IITimeLine>                    (Infrastructure::GetContext(), count);
    }
}

#endif