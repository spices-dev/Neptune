/**
* @file Fence.cpp.
* @brief The Fence Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Fence.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    Fence::Fence(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void Fence::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        VkFenceCreateInfo             fenceInfo{};
		fenceInfo.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

        for (uint32_t i = 0; i < count; ++i)
        {
            auto fence = CreateUP<Unit::Fence>();

            fence->CreateFence(GetContext().Get<IDevice>()->Handle(), fenceInfo);
 
            DEBUGUTILS_SETOBJECTNAME(*fence, ToString())

            m_Fences.emplace_back(std::move(fence));
        }
    }

    void Fence::Wait(uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE

        auto& fence = m_Fences[index];

        fence->Wait();

        fence->ResetFence();
    }

    void Fence::WaitAll() const
    {
        NEPTUNE_PROFILE_ZONE

        std::ranges::for_each(m_Fences, [](const auto& fence) {
            
            fence->Wait();

            fence->ResetFence();
        });
    }

}

#endif