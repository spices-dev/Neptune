/**
* @file CommandQueue.cpp.
* @brief The CommandQueue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "CommandQueue.h"
#include "Device.h"

namespace Neptune::Metal {
	
    CommandQueue::CommandQueue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE
        
        Create();
    }
    
    void CommandQueue::Create()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_CommandQueue.CreateCommandQueue(GetContext().Get<IDevice>()->Handle());
    }
    
}

#endif