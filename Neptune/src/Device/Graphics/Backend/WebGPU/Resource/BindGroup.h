/**
* @file BindGroup.h.
* @brief The BindGroup Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/BindGroup.h"
#include "Device/Graphics/Backend/WebGPU/Unit/BindGroupLayout.h"

#include <map>
#include <vector>
#include <variant>

namespace Neptune::WebGPU {
	
	class RenderTarget;
}

namespace Neptune::WebGPU::Resource {

	/**
	* @brief WebGPU::BindGroup Class.
	* This class defines the WebGPU::BindGroup behaves.
	*/
	class BindGroup : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit BindGroup(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~BindGroup() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::BindGroup::Handle& Handle() const { return m_BindGroup.GetHandle(); }

		/**
		* @brief Add BindGroup Binding.
		*
		* @param[in] desc WGPUBufferDescriptor.
		* @param[in] entry WGPUBindGroupLayoutEntry.
		*/
		void AddBinding(const WGPUBufferDescriptor& desc, const WGPUBindGroupLayoutEntry& entry);

		/**
		* @brief Add BindGroup Binding.
		*
		* @param[in] imageInfo WGPUBindGroupEntry.
		* @param[in] entry WGPUBindGroupLayoutEntry.
		*/
		void AddBinding(const WGPUBindGroupEntry& imageInfo, const WGPUBindGroupLayoutEntry& entry);
		
		/**
		* @brief Update Buffer Binding.
		*
		* @param[in] binding .
		* @param[in] data Buffer Data.
		*/
		void UpdateBuffer(uint32_t binding, const void* data);

		/**
		* @brief Update Texture Binding.
		*
		* @param[in] binding .
		* @param[in] renderTarget RenderTarget.
		*/
		void UpdateTexture(uint32_t binding, const RenderTarget* renderTarget);

		/**
		* @brief Update DynamicUniformBufferOffset.
		*
		* @param[in] offset .
		*/
		void UpdateDynamicUniformBufferOffset(uint32_t offset);
		
		/**
		* @brief Build BindGroup.
		*/
		void BuildBindGroup();

		/**
		* @brief Update BindGroup.
		*/
		void UpdateBindGroup();

		/**
		* @brief Get BindGroupLayout Unit Handle.
		*
		* @return Returns BindGroupLayout Unit Handle.
		*/
		const Unit::BindGroupLayout::Handle& GetBindGroupLayout() const { return m_Layout.GetHandle(); }

		/**
		* @brief Get Binding Offset.
		*
		* @return Returns Binding Offset.
		*/
		uint32_t GetOffset() const { return m_Offset; }
		
	private:

		/**
		* @brief Create BindGroupLayout.
		*/
		void CreateBindGroupLayout();

	private:

		/**
		* @brief Buffer Binding Data
		*/
		struct BufferBindingData 
		{
			SP<class Buffer> buffer;                                    // @brief Buffer Reference.
			WGPUBindGroupEntry bufferInfo;                              // @brief VkDescriptorBufferInfo.
		};										                       

		/**
		* @brief Image Binding Data
		*/
		struct ImageBindingData 
		{
			std::vector<WGPUBindGroupEntry> imageInfos;                 // @brief VkDescriptorImageInfo.
		};

		/**
		* @brief Binding Data
		*/
		struct BindingData 
		{
			WGPUBindGroupLayoutEntry  binding;                          // @brief WGPUBindGroupLayoutEntry.
			std::variant<BufferBindingData, ImageBindingData> data;     // @brief Specific Binding.
		};
		
		Unit::BindGroup                                 m_BindGroup;          // @brief This BindGroup.
		Unit::BindGroupLayout                           m_Layout;             // @brief This BindGroupLayout.
		std::map<uint32_t, BindingData>                 m_Bindings;           // @brief This Binding.
		uint32_t                                        m_Offset;             // @brief This Binding Offset.
	};
}

#endif