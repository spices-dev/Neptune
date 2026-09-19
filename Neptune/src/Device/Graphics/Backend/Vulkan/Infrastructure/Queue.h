/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Queue.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/IQueueSubmit.h"

namespace Neptune::Vulkan {

	using IGraphicQueue     = IInfrastructure<class Queue, EInfrastructure::GraphicQueue>;
	using IPresentQueue     = IInfrastructure<class Queue, EInfrastructure::PresentQueue>;
	using IComputeQueue     = IInfrastructure<class Queue, EInfrastructure::ComputeQueue>;

	/**
	* @brief Vulkan::Queue Class.
	* This class defines the Vulkan::Queue behaves.
	*/
	class Queue : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Queue(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Queue() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Queue::Handle& Handle() const { return m_Queue.GetHandle(); }

		/**
		* @brief Submit CommandBuffer to Queue.
		*
		* @param[in] info VkSubmitInfo2.
		* @param[in] fence VkFence.
		*/
		void Submit(const VkSubmitInfo2& info, VkFence fence = VK_NULL_HANDLE) const;
		
		/**
		* @brief Queue Wait idle.
		*/
		void Wait() const;

	private:

		/**
		* @brief Create Queue.
		*/
		void Create();

		/**
		* @brief Get Queue Family.
		* 
		* @return Returns Queue Family
		*/
		uint32_t GetQueueFamily() const;

	private:

		Unit::Queue m_Queue;                           // @brief This Queue.
		UP<Middleware::IQueueSubmit> m_QueueSubmit;    // @brief This QueueSubmit.
	};

}

#endif