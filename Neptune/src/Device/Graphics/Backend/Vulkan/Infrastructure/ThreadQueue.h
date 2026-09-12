/**
* @file ThreadQueue.h.
* @brief The ThreadQueue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Resource/Queue.h"
#include "Core/Container/ThreadQueue.h"

namespace Neptune::Vulkan {

	using IGraphicThreadQueue     = IInfrastructure<class ThreadQueue, EInfrastructure::GraphicThreadQueue>;
	using IComputeThreadQueue     = IInfrastructure<class ThreadQueue, EInfrastructure::ComputeThreadQueue>;
	using ITransferThreadQueue    = IInfrastructure<class ThreadQueue, EInfrastructure::TransferThreadQueue>;
	using IVideoEncodeThreadQueue = IInfrastructure<class ThreadQueue, EInfrastructure::VideoEncodeThreadQueue>;
	using IVideoDecodeThreadQueue = IInfrastructure<class ThreadQueue, EInfrastructure::VideoDecodeThreadQueue>;
	using IOpticalFlowThreadQueue = IInfrastructure<class ThreadQueue, EInfrastructure::OpticalFlowThreadQueue>;

	/**
	* @brief Vulkan::ThreadQueue Class.
	* This class defines the Vulkan::ThreadQueue behaves.
	*/
	class ThreadQueue : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		ThreadQueue(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~ThreadQueue() override = default;

		/**
		* @brief Pop a Queue.
		* 
		* @return Returns Queue.
		*/
		SP<Resource::Queue> Pop() { return m_Queues.Pop(); }

		/**
		* @brief Push a Queue.
		*
		* @param[in] queue Queue.
		*/
		void Push(const SP<Resource::Queue>& queue) { m_Queues.Push(queue); }

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
		
		/**
		* @brief Get Queue Family Count.
		* 
		* @return Returns Queue Family Count
		*/
		uint32_t GetQueueFamilyCount() const;

	private:

		Container::ThreadQueue<SP<Resource::Queue>> m_Queues;   // @brief Container of Queue.

	};
	
}

#endif