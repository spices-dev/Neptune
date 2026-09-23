/**
* @file CommandBuffer.cpp.
* @brief The CommandBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_METAL

#include "CommandBuffer.h"
#include "CommandQueue.h"

namespace Neptune::Metal {
	
    CommandBuffer::CommandBuffer(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE
        
        Create();
    }
    
    void CommandBuffer::Create()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_CommandBuffer.CreateCommandBuffer(GetContext().Get<ICommandQueue>()->Handle());
    }
    
}

#endif