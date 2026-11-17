/**
* @file SwapChainFence.h.
* @brief The SwapChainFence Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Fence.h"

namespace Neptune::Vulkan::Resource {

	/**
	* @brief Vulkan::SwapChainFence Class.
	* This class defines the Vulkan::SwapChainFence behaves.
	*/
	class SwapChainFence : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit SwapChainFence(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~SwapChainFence() override = default;

		/**
		* @brief Create SwapChainFence.
		*
		* @param[in] info VkFenceCreateInfo.
		*/
		void CreateSwapChainFence(const VkFenceCreateInfo& info);
		
		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Fence::Handle& Handle() const { return m_Fence.GetHandle(); }

		/**
		* @brief SwapChainFence wait idle and reset.
		*/
		void WaitReset();
		
		/**
		* @brief Reset SwapChainFence.
		*/
		void ResetFence() const;
		
	private:

		Unit::Fence m_Fence;              // @brief This Fence.
		bool        m_FirstEntry = true;  // @brief First Entry.
	};
}

#endif