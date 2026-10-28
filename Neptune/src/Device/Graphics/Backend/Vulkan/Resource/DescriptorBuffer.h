/**
* @file DescriptorBuffer.h.
* @brief The DescriptorBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/DescriptorSetLayout.h"

#include <map>
#include <vector>
#include <variant>

namespace Neptune::Vulkan {
	
	class RenderTarget;
	class Buffer;
}

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
		* @brief Add DescriptorSet Binding.
		*
		* @param[in] info VkBufferCreateInfo.
		* @param[in] binding VkDescriptorSetLayoutBinding.
		*/
		void AddBinding(const VkBufferCreateInfo& info, const VkDescriptorSetLayoutBinding& binding);

		/**
		* @brief Add DescriptorSet Binding.
		*
		* @param[in] info VkDescriptorImageInfo.
		* @param[in] binding VkDescriptorSetLayoutBinding.
		*/
		void AddBinding(const VkDescriptorImageInfo& info, const VkDescriptorSetLayoutBinding& binding);

		/**
		* @brief Update Buffer Binding.
		*
		* @param[in] binding .
		* @param[in] data Buffer Data.
		*/
		void UpdateBuffer(uint32_t binding, const void* data);

		/**
		* @brief Update Uniform Binding.
		*
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void UpdateUniformTexture(uint32_t binding, const RenderTarget* renderTarget);

		/**
		* @brief Update Storage Binding.
		*
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void UpdateStorageTexture(uint32_t binding, const RenderTarget* renderTarget);

		/**
		* @brief Update DynamicUniformBufferOffset.
		*
		* @param[in] offset .
		*/
		void UpdateDynamicUniformBufferOffset(uint32_t offset);
		
		/**
		* @brief Build DescriptorBuffer.
		*/
		void BuildDescriptorBuffer();

		/**
		* @brief Update DescriptorBuffer.
		*/
		void UpdateDescriptorBuffer();
		
		/**
		* @brief Get DescriptorSetLayout Unit Handle.
		*
		* @return Returns DescriptorSetLayout Unit Handle.
		*/
		const Unit::DescriptorSetLayout::Handle& GetDescriptorSetLayout() const { return m_Layout.GetHandle(); }

		/**
		* @brief Get Binding Offset.
		*
		* @return Returns Binding Offset.
		*/
		const std::optional<uint32_t>& GetOffset() const { return m_Offset; }
		
	private:

		/**
		* @brief Create DescriptorSetLayout.
		*/
		void CreateDescriptorSetLayout();

		/**
		* @brief Update DescriptorStagingBuffer.
		* 
		* @param[in] binding .
		*/
		void UpdateDescriptorStagingBuffer(uint32_t binding) const;
		
		/**
		* @brief Upload DescriptorStagingBuffer.
		* 
		* @param[in] binding .
		*/
		void UploadDescriptorStagingBuffer(uint32_t binding) const;
		
		/**
		* @brief Get Binding Desc Size.
		* 
		* @param[in] type VkDescriptorType.
		* 
		* @return Returns Binding Desc Size.
		*/
		uint64_t GetBindingDescSize(VkDescriptorType type) const;
		
		/**
		* @brief Get Binding DescriptorBuffer.
		* 
		* @param[in] type VkDescriptorType.
		* 
		* @return Returns Binding DescriptorBuffer.
		*/
		Buffer* GetBindingDescriptorBuffer(VkDescriptorType type) const;
		
	private:

		/**
		* @brief Buffer Binding Data
		*/
		struct BufferBindingData 
		{
			SP<Buffer> buffer;                                    // @brief Buffer Reference.
			VkDescriptorBufferInfo bufferInfo;                    // @brief VkDescriptorBufferInfo.
		};										                       

		/**
		* @brief Image Binding Data
		*/
		struct ImageBindingData 
		{
			std::vector<VkDescriptorImageInfo> imageInfos;              // @brief VkDescriptorImageInfo.
		};

		/**
		* @brief Binding Data
		*/
		struct BindingData 
		{
			VkDescriptorSetLayoutBinding  binding;                      // @brief VkDescriptorSetLayoutBinding.
			uint64_t offset = 0;                                        // @brief Binding Offset.
			std::variant<BufferBindingData, ImageBindingData> data;     // @brief Specific Binding.
		};

		std::unordered_map<VkBufferUsageFlagBits, UP<Buffer>> m_DescriptorBuffer;          // @brief This DescriptorBuffer.
		uint64_t                                          	  m_LayoutSize = 0;            // @brief This DescriptorSetLayout Size.
		Unit::DescriptorSetLayout                         	  m_Layout;                    // @brief This DescriptorSetLayout.
		std::map<uint32_t, BindingData>                   	  m_Bindings;                  // @brief This Binding.
		std::optional<uint32_t>                           	  m_Offset;                    // @brief This Binding Offset.
	};
}

#endif