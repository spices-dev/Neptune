/**
* @file Layer.cpp.
* @brief The Layer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "Layer.h"
#include "Device.h"

namespace Neptune::Metal {
	
    Layer::Layer(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void Layer::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Layer.CreateLayer();
        
        auto layer = m_Layer.GetHandle();
        
        layer->setDevice(GetContext().Get<IDevice>()->Handle());
        
        layer->setPixelFormat(MTL::PixelFormat::PixelFormatRGBA8Unorm);
        
        layer->setFramebufferOnly(true);
        
        layer->setMaximumDrawableCount(count);
    }
    
    void Layer::NextDrawable()
    {
        m_Layer.GetHandle()->nextDrawable();
    }
}

#endif