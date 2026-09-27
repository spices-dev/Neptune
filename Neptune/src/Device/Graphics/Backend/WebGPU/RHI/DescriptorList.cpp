/**
* @file DescriptorList.cpp.
* @brief The DescriptorList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "DescriptorList.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/RHI/RenderTarget.h"

namespace Neptune::WebGPU {

	void DescriptorList::AddShaderConstant(uint32_t bytes)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_ImmediateSize = bytes;
	}
	
	void DescriptorList::AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes)
	{
		NEPTUNE_PROFILE_ZONE
		
		auto bindGroup = AccessSet(set);

		WGPUBufferDescriptor              desc{};
		desc.usage                      = WGPUBufferUsage_Uniform;
		desc.size                       = bytes;
		desc.mappedAtCreation           = false;
		
		WGPUBindGroupLayoutEntry          entry{};
		entry.binding                   = binding;
		entry.visibility                = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment | WGPUShaderStage_Compute;
		entry.bindingArraySize          = 0;
		entry.buffer.type               = WGPUBufferBindingType_Uniform;
		entry.buffer.minBindingSize     = bytes;
		entry.buffer.hasDynamicOffset   = 0;
		
		bindGroup->AddBinding(desc, entry);
	}
	
	void DescriptorList::AddDynamicUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes)
	{
		NEPTUNE_PROFILE_ZONE
		
		auto bindGroup = AccessSet(set);

		WGPUBufferDescriptor              desc{};
		desc.usage                      = WGPUBufferUsage_Uniform;
		desc.size                       = bytes;
		desc.mappedAtCreation           = false;
		
		WGPUBindGroupLayoutEntry          entry{};
		entry.binding                   = binding;
		entry.visibility                = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment | WGPUShaderStage_Compute;
		entry.buffer.type               = WGPUBufferBindingType_Uniform;
		entry.buffer.minBindingSize     = bytes;
		entry.buffer.hasDynamicOffset   = 1;
		
		bindGroup->AddBinding(desc, entry);
		
		bindGroup->UpdateDynamicUniformBufferOffset(0);
	}

	void DescriptorList::AddUniformTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE
		
		auto bindGroup = AccessSet(set);

		WGPUBindGroupEntry                imageInfo{};
		imageInfo.binding               = binding;
		imageInfo.sampler               = renderTarget->GetRHIImpl<RenderTarget>()->GetSampler();
		imageInfo.textureView           = renderTarget->GetRHIImpl<RenderTarget>()->GetView();
		
		WGPUBindGroupLayoutEntry          entry{};
		entry.binding                   = binding;
		entry.visibility                = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment | WGPUShaderStage_Compute;
		entry.sampler.type              = WGPUSamplerBindingType_Filtering;
		
		bindGroup->AddBinding(imageInfo, entry);
	}

	void DescriptorList::UpdateUniformBuffer(uint32_t set, uint32_t binding, const void* data)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_BindGroup[set]->UpdateBuffer(binding, data);
	}

	void DescriptorList::UpdateUniformTexture(uint32_t set, uint32_t binding, const SP<RHI::RenderTarget>& renderTarget)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_BindGroup[set]->UpdateTexture(binding, renderTarget->GetRHIImpl<RenderTarget>());
	}
	
	void DescriptorList::UpdateDynamicUniformBufferOffset(uint32_t set, uint32_t offset)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_BindGroup[set]->UpdateDynamicUniformBufferOffset(offset);
	}

	void DescriptorList::CombineSharedLayout(const RHI::RHIDescriptorList::Impl* shared)
	{
		NEPTUNE_PROFILE_ZONE

		auto p = dynamic_cast<const DescriptorList*>(shared);

		m_BindGrouLayouts.insert(m_BindGrouLayouts.begin(), p->GetLayouts().begin(), p->GetLayouts().end());
	}

	void DescriptorList::Build()
	{
		NEPTUNE_PROFILE_ZONE
		
		std::ranges::for_each(m_BindGroup, [](const auto& pair) {
			
			pair.second->BuildBindGroup();
		});
		
		std::ranges::for_each(m_BindGroup, [&](const auto& pair) {

			m_BindGrouLayouts.emplace_back(pair.second->GetBindGroupLayout());
		});
	}

	SP<Resource::BindGroup> DescriptorList::AccessSet(uint32_t set)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (!m_BindGroup.contains(set))
		{
			m_BindGroup[set] = CreateSP<Resource::BindGroup>(GetContext());
		}

		return m_BindGroup.at(set);
	}
}

#endif