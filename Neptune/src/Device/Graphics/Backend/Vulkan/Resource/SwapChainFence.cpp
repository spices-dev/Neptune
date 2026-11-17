/**
* @file SwapChainFence.cpp.
* @brief The SwapChainFence Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SwapChainFence.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Vulkan::Resource {

    void SwapChainFence::CreateSwapChainFence(const VkFenceCreateInfo& info)
    {
        NEPTUNE_PROFILE_ZONE

        m_FirstEntry = true;
        
        m_Fence.CreateFence(GetContext().Get<IDevice>()->Handle(), info);
        
        DEBUGUTILS_SETOBJECTNAME(m_Fence, "SwapChainFence")
    }

    void SwapChainFence::WaitReset()
    {
        NEPTUNE_PROFILE_ZONE
        
        if (m_FirstEntry)
        {
            m_FirstEntry = false;
            
            return;
        }
        
        m_Fence.Wait();
        
        m_Fence.ResetFence();
    }
    
    void SwapChainFence::ResetFence() const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Fence.ResetFence();
    }
    
}

#endif