/**
* @file Presenter.cpp.
* @brief The Presenter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Presenter.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {
    
    Presenter::Presenter(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

    const Unit::ImageView::Handle& Presenter::GetView(EPresenter position) const
    {
        NEPTUNE_PROFILE_ZONE
        
        auto& item = m_Presenters[static_cast<uint8_t>(position)];
        
        return item->swapChain->GetView(item->imageIndex);
    }

    const Unit::Image::Handle& Presenter::GetImage(EPresenter position) const
    {
        NEPTUNE_PROFILE_ZONE
        
        auto& item = m_Presenters[static_cast<uint8_t>(position)];
        
        return item->swapChain->GetImage(item->imageIndex);
    }

    void Presenter::Create(EPresenter position, uint32_t count, Unit::SwapChain::Handle handle)
    {
        NEPTUNE_PROFILE_ZONE

        auto item = CreateUP<Item>();
        
        item->swapChain = CreateUP<Resource::SwapChain>(GetContext(), count, handle);
        
        VkSemaphoreCreateInfo              semaphoreInfo {};
        semaphoreInfo.sType              = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
        {
            auto semaphore = CreateUP<Unit::Semaphore>();

            semaphore->CreateSemaphore(GetContext().Get<IDevice>()->Handle(), semaphoreInfo);

            DEBUGUTILS_SETOBJECTNAME(*semaphore, "SwapChainImageSemaphore")

            item->semaphores[i] = std::move(semaphore);
        }
        
        m_Presenters[static_cast<uint8_t>(position)] = std::move(item);
    }

    void Presenter::View(const std::function<void(EPresenter position, Item* item)>& iter) const
    {
        NEPTUNE_PROFILE_ZONE
        
        for (uint8_t i = 0 ; i < m_Presenters.size(); ++i)
        {
            if (!m_Presenters[i]) continue;
            
            std::invoke(iter, static_cast<EPresenter>(i), m_Presenters[i].get());
        }
    }
    
    std::set<EPresenter> Presenter::GetNextImage(uint64_t frameId) const
    {
        NEPTUNE_PROFILE_ZONE
        
        std::set<EPresenter> result;
        
        for (uint8_t i = 0 ; i < m_Presenters.size(); ++i)
        {
            if (!m_Presenters[i]) continue;
            
            auto& item = m_Presenters[i];
            
            if (!item->swapChain->GetNextImage(item->semaphores[frameId % MaxFrameInFlight]->GetHandle(), item->imageIndex))
            {
                result.insert(static_cast<EPresenter>(i));
            }
        }
        
        return result;
    }

    std::vector<VkSemaphoreSubmitInfo> Presenter::GetWaitInfo(uint64_t frameId) const
    {
        NEPTUNE_PROFILE_ZONE
        
        std::vector<VkSemaphoreSubmitInfo> infos;
        
        for (const auto& item : m_Presenters)
        {
            if (!item) continue;
            
            VkSemaphoreSubmitInfo                 waitInfo{};
            waitInfo.sType                      = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO;
            waitInfo.stageMask                  = VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT;
            waitInfo.semaphore                  = item->semaphores[frameId % MaxFrameInFlight]->GetHandle();
			
            infos.emplace_back(waitInfo);
        }
        
        return infos;
    }

    std::set<EPresenter> Presenter::Present(VkPresentInfoKHR& info, uint64_t frameId) const
    {
        NEPTUNE_PROFILE_ZONE
        
        std::set<EPresenter> result;
        
        for (uint8_t i = 0 ; i < m_Presenters.size(); ++i)
        {
            if (!m_Presenters[i]) continue;
            
            auto& item = m_Presenters[i];
            
            info.swapchainCount  = 1;
            info.pImageIndices   = &item->imageIndex;
            
            if (!item->swapChain->Present(info, frameId))
            {
                result.insert(static_cast<EPresenter>(i));
            }
        }
        
        return result;
    }
}

#endif
