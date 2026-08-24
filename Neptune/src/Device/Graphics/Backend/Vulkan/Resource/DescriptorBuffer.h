/**
* @file DescriptorBuffer.h.
* @brief The DescriptorBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Buffer.h"
#include "Device/Graphics/Backend/Vulkan/Unit/DescriptorSetLayout.h"

namespace Neptune::Vulkan::Resource {

	/**
	* @brief Vulkan::DescriptorBuffer Class.
	* This class defines the Vulkan::DescriptorBuffer behaves.
	*/
	class DescriptorBuffer : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit DescriptorBuffer(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~DescriptorBuffer() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Buffer::Handle& Handle() const { return m_Buffer.GetHandle(); }
		
		/**
		* @brief Get DescriptorSetLayout Unit Handle.
		*
		* @return Returns DescriptorSetLayout Unit Handle.
		*/
		const Unit::DescriptorSetLayout::Handle& GetDescriptorSetLayout() const { return m_Layout.GetHandle(); }

	private:

		Unit::Buffer                              m_Buffer;             // @brief This DescriptorBuffer.
		Unit::DescriptorSetLayout                 m_Layout;             // @brief This DescriptorSetLayout.
	};
}

#endif