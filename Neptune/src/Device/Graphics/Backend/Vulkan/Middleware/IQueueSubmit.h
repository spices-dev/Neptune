/**
* @file IQueueSubmit.h.
* @brief The IQueueSubmit Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan::Unit {
	
	class Queue;
}

namespace Neptune::Vulkan::Middleware {
	
    /**
    * @brief Interface of IQueueSubmit.
    */
    class IQueueSubmit
    {
    public:
		
        /**
        * @brief Create IQueueSubmit.
        * 
        * @param context Context.
        * 
        * @return Returns IQueueSubmit.
        */
        static UP<IQueueSubmit> Create(const Context& context);
		
        /**
        * @brief Destructor Function.
        */
        virtual ~IQueueSubmit() = default;
    	
    	/**
		* @brief Interface of Submit.
		* 
		* @param[in] queue Queue.
		* @param[in] info VkSubmitInfo2.
		* @param[in] fence VkFence.
		*/
    	virtual void Submit(const Unit::Queue* queue, const VkSubmitInfo2& info, VkFence fence = VK_NULL_HANDLE) const = 0;
    };
	
	/**
	* @brief Implement of QueueSubmit.
	*/
	class QueueSubmit : public IQueueSubmit
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		QueueSubmit() = default;

		/**
		* @brief Destructor Function.
		*/
		~QueueSubmit() override = default;
		
		/**
		* @brief Interface of Submit.
		* 
		* @param[in] queue Queue.
		* @param[in] info VkSubmitInfo2.
		* @param[in] fence VkFence.
		*/
		void Submit(const Unit::Queue* queue, const VkSubmitInfo2& info, VkFence fence = VK_NULL_HANDLE) const override;
	};
	
	/**
	* @brief Implement of GetSurfaceCapabilities2.
	*/
	class QueueSubmit2 : public IQueueSubmit
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		QueueSubmit2() = default;

		/**
		* @brief Destructor Function.
		*/
		~QueueSubmit2() override = default;
		
		/**
		* @brief Interface of Submit.
		* 
		* @param[in] queue Queue.
		* @param[in] info VkSubmitInfo2.
		* @param[in] fence VkFence.
		*/
		void Submit(const Unit::Queue* queue, const VkSubmitInfo2& info, VkFence fence = VK_NULL_HANDLE) const override;
	};
}

#endif