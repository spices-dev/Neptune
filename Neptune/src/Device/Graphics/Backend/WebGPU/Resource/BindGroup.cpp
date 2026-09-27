/**
* @file BindGroup.cpp.
* @brief The BindGroup Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "BindGroup.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"
#include "Device/Graphics/Backend/WebGPU/RHI/RenderTarget.h"
#include "Buffer.h"

namespace Neptune::WebGPU::Resource {

	void BindGroup::AddBinding(const WGPUBufferDescriptor& desc, const WGPUBindGroupLayoutEntry& entry)
	{
		NEPTUNE_PROFILE_ZONE

		auto buffer = CreateSP<Buffer>(GetContext());
		
		buffer->CreateBuffer(desc);

		buffer->SetName("UniformBuffer");
		
		BufferBindingData                      data{};
		data.buffer                          = buffer;
		data.bufferInfo.binding              = entry.binding;
		data.bufferInfo.buffer               = buffer->Handle();
		data.bufferInfo.offset               = 0;
		data.bufferInfo.size                 = buffer->Size();
		
		m_Bindings.emplace(entry.binding, BindingData { entry, data });
	}

	void BindGroup::AddBinding(const WGPUBindGroupEntry& imageInfo, const WGPUBindGroupLayoutEntry& entry)
	{
		NEPTUNE_PROFILE_ZONE
		
		ImageBindingData data{};
		data.imageInfos.emplace_back(imageInfo);

		m_Bindings.emplace(entry.binding, BindingData{ entry, data });
	}
	
	void BindGroup::UpdateBuffer(uint32_t binding, const void* data)
	{
		NEPTUNE_PROFILE_ZONE

		auto buffer = std::get<BufferBindingData>(m_Bindings[binding].data).buffer;

		buffer->MapHostMemory();
		
		buffer->WriteToBuffer(data);

		buffer->UnapHostMemory();
	}

	void BindGroup::UpdateTexture(uint32_t binding, const RenderTarget* renderTarget)
	{
		NEPTUNE_PROFILE_ZONE
		
		auto& imageInfos = std::get<ImageBindingData>(m_Bindings[binding].data).imageInfos;

		imageInfos[0].sampler           = renderTarget->GetSampler();
		imageInfos[0].textureView       = renderTarget->GetView();

		UpdateBindGroup();
	}

	void BindGroup::UpdateDynamicUniformBufferOffset(uint32_t offset)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Offset = offset;
	}
	
	void BindGroup::BuildBindGroup()
	{
		NEPTUNE_PROFILE_ZONE

		CreateBindGroupLayout();
		
		UpdateBindGroup();
	}

	void BindGroup::UpdateBindGroup()
	{
		NEPTUNE_PROFILE_ZONE

		std::vector<WGPUBindGroupEntry> entries;
		
		for (const auto& binding : m_Bindings | std::views::values)
		{
			if (auto* p = std::get_if<BufferBindingData>(&binding.data))
			{
				entries.emplace_back(p->bufferInfo);
			}
			else if (auto* p = std::get_if<ImageBindingData>(&binding.data))
			{
				entries.insert(entries.end(), p->imageInfos.begin(), p->imageInfos.end());
			}
		}
		
		WGPUBindGroupDescriptor        desc{};
		desc.layout                  = m_Layout.GetHandle();
		desc.entryCount              = entries.size();
		desc.entries                 = entries.data();
		
		m_BindGroup.CreateBindGroup(GetContext().Get<IDevice>()->Handle(), desc);
		
		DEBUGUTILS_SETOBJECTNAME(m_BindGroup, "BindGroup")
	}

	void BindGroup::CreateBindGroupLayout()
	{
		NEPTUNE_PROFILE_ZONE

		std::vector<WGPUBindGroupLayoutEntry> entries;
		
		for (const auto& binding : m_Bindings | std::views::values)
		{
			entries.emplace_back(binding.binding);
		}
		
		WGPUBindGroupLayoutDescriptor       desc{};
		desc.entryCount                   = entries.size();
		desc.entries                      = entries.data();
		
		m_Layout.CreateBindGroupLayout(GetContext().Get<IDevice>()->Handle(), desc);
		
		DEBUGUTILS_SETOBJECTNAME(m_Layout, "BindGroupLayout")
	}
}

#endif