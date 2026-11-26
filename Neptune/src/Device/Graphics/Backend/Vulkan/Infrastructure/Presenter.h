/**
* @file Presenter.h.
* @brief The Presenter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Semaphore.h"
#include "Device/Graphics/Backend/Vulkan/Resource/SwapChain.h"
#include  "Slate/Frontend/Enum.h"

#include <vector>

namespace Neptune::Vulkan {
	
	using IPresenter = IInfrastructure<class Presenter, EInfrastructure::Presenter>;

	/**
	* @brief Vulkan::Presenter Class.
	* This class defines the Vulkan::Presenter behaves.
	*/
	class Presenter : public Infrastructure
	{
	public:
		
		struct Item 
		{
			UP<Resource::SwapChain>                           swapChain;             // @brief Item SwapChain.
			std::array<UP<Unit::Semaphore>, MaxFrameInFlight> semaphores;            // @brief Item Semaphores.
			uint32_t                                          imageIndex = 0;        // @brief Item SwapChainImage Index.
		};
		
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Presenter(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Presenter() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @param[in] position EPresenter.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::SwapChain::Handle& Handle(EPresenter position) const { return m_Presenters[static_cast<uint8_t>(position)]->swapChain->Handle(); }

		/**
		* @brief Get Resource Handle.
		*
		* @param[in] position EPresenter.
		* 
		* @return Returns Resource Handle.
		*/
		const Resource::SwapChain& IHandle(EPresenter position) const { return *m_Presenters[static_cast<uint8_t>(position)]->swapChain; }
		
		/**
		* @brief Get ImageIndex.
		*
		* @param[in] position EPresenter.
		* 
		* @return Returns ImageIndex.
		*/
		uint32_t ImageIndex(EPresenter position) const { return m_Presenters[static_cast<uint8_t>(position)]->imageIndex; }
		
		/**
		* @brief Get Unit ImageView Handle.
		*
		* @param[in] position EPresenter.
		* 
		* @return Returns Unit ImageView Handle.
		*/
		const Unit::ImageView::Handle& GetView(EPresenter position) const;
		
		/**
		* @brief Get Unit Image Handle.
		*
		* @param[in] position EPresenter.
		* 
		* @return Returns Unit Image Handle.
		*/
		const Unit::Image::Handle& GetImage(EPresenter position) const;
		
		/**
		* @brief Create ImageSemaphores.
		* 
		* @param[in] position EPresenter.
		* @param[in] count SwapChain image Count.
		* @param[in] handle Old SwapChain Handle.
		*/
		void Create(EPresenter position, uint32_t count, Unit::SwapChain::Handle handle = VK_NULL_HANDLE);
		
		/**
		* @brief View Presenters.
		*
		* @param[in] iter Iter function.
		*/
		void View(const std::function<void(EPresenter position, Item* item)>& iter) const;
		
		/**
		* @brief Get Next SwapChain Image.
		*
		* @param[in] frameId .
		* 
		* @return Returns failed EPresenter.
		*/
		std::set<EPresenter> GetNextImage(uint64_t frameId) const;
		
		/**
		* @brief Get VkSemaphoreSubmitInfo.
		*
		* @param[in] frameId .
		* 
		* @return Returns VkSemaphoreSubmitInfo.
		*/
		std::vector<VkSemaphoreSubmitInfo> GetWaitInfo(uint64_t frameId) const;
		
		/**
		* @brief Present to surface.
		*
		* @param[in] info VkPresentInfoKHR.
		* @param[in] frameId FrameId.
		*
		* @return Returns failed EPresenter.
		*/
		std::set<EPresenter> Present(VkPresentInfoKHR& info, uint64_t frameId) const;
		
	private:
		
		std::array<UP<Item>, static_cast<uint8_t>(EPresenter::Count)> m_Presenters;    // @brief Presenters.
		
	};

}

#endif