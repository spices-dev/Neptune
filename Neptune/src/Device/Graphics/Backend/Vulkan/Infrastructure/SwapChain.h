/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/SwapChain.h"
#include "Device/Graphics/Backend/Vulkan/Resource/Image.h"

namespace Neptune::Vulkan {

	/**
	* @brief Runtime state of VK_EXT_present_timing for one swapchain.
	*/
	struct PresentTimingState
	{
		uint64_t                timeDomainId      = 0;
		VkPresentStageFlagsEXT  targetStage       = 0;       // @brief Non-zero only when a stage-local time domain is used.
		
		uint64_t                domainsCounter    = 0;
		VkPresentStageFlagsEXT  stage             = VK_PRESENT_STAGE_QUEUE_OPERATIONS_END_BIT_EXT;

		uint32_t                queueSize         = 0;       // @brief Size of the swapchain internal result queue.
		uint32_t                pending           = 0;       // @brief Presents which still occupy a result slot.

		uint64_t                           tpCount      = 0;
		VkSwapchainTimingPropertiesEXT     tp{};

		// Latest completed result, used as baseline for scheduling.
		uint64_t                lastPresentId     = 0;
		uint64_t                lastPresentTime   = 0;

		static constexpr uint32_t kMaxStages = 4;
		std::vector<VkPastPresentationTimingEXT> timings;
		std::vector<VkPresentStageTimeEXT>       stageTimes;
	};
	
	using ISwapChain = IInfrastructure<class SwapChain, EInfrastructure::SwapChain>;

	/**
	* @brief Vulkan::SwapChain Class.
	* This class defines the Vulkan::SwapChain behaves.
	*/
	class SwapChain : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count SwapChain image Count.
		* @param[in] handle Old SwapChain Handle.
		*/
		SwapChain(Context& context, EInfrastructure e, uint32_t count, Unit::SwapChain::Handle handle = VK_NULL_HANDLE);

		/**
		* @brief Destructor Function.
		*/
		~SwapChain() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::SwapChain::Handle& Handle() const { return m_SwapChain->GetHandle(); }

		/**
		* @brief Get Next SwapChain Image.
		*
		* @param[in] semaphore VkSemaphore.
		* @param[out] imageIndex Next SwapChain Image index.
		* 
		* @return Returns true if found.
		*/
		bool GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const;

		/**
		* @brief Get ImageView Unit Handle.
		*
		* @param[in] index ImageView index.
		* 
		* @return Returns ImageView Unit Handle.
		*/
		const Unit::ImageView::Handle& GetView(uint32_t index) const { return m_SwapChainImage[index]->GetView(); }

		/**
		* @brief Get Image Unit Handle.
		*
		* @param[in] index Image index.
		* 
		* @return Returns Image Unit Handle.
		*/
		const Unit::Image::Handle& GetImage(uint32_t index) const { return m_SwapChainImage[index]->Handle(); }
		
		/**
		* @brief Present to surface.
		*
		* @param[in] info VkPresentInfoKHR.
		* @param[in] frameId FrameId.
		*
		* @return Returns true if succeeded.
		*/
		bool Present(VkPresentInfoKHR& info, uint64_t frameId);

	private:

		/**
		* @brief Create SwapChain.
		*
		* @param[in] count SwapChain image count.
		* @param[in] handle Old SwapChain Handle.
		*/
		void Create(uint32_t count, Unit::SwapChain::Handle handle = VK_NULL_HANDLE);

		void PollPresentTiming();
		bool QueryTimeDomains();
		void QueryTimingProperties();
		uint64_t ComputeTargetTime(uint64_t presentId) const;
		
	private:

		UP<Unit::SwapChain> m_SwapChain;                     // @brief This SwapChain.
		std::vector<UP<Resource::Image>> m_SwapChainImage;   // @brief Container of SwapChainImage.
		PresentTimingState m_PresentTimingState;             // @brief PresentTimingState.
		uint64_t m_TargetFrameInterval = 0;                  // @brief Target image present duration in ns.

	};

}

#endif