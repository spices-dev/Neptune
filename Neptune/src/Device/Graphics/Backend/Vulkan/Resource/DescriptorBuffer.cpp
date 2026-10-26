/**
* @file DescriptorBuffer.cpp.
* @brief The DescriptorBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DescriptorBuffer.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderTarget.h"
#include "Buffer.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/DescriptorBuffer.h"
#include "Core/Math/Math.h"
#include "Device/Graphics/Backend/Vulkan/RHI/CmdList2.h"

namespace Neptune::Vulkan::Resource {

	void DescriptorBuffer::AddBinding(const VkBufferCreateInfo& info, const VkDescriptorSetLayoutBinding& binding)
	{
		NEPTUNE_PROFILE_ZONE

		auto buffer = CreateSP<Buffer>(GetContext());
		
		buffer->CreateBuffer(info, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

		buffer->SetName("UniformBuffer");

		BufferBindingData                 data{};
		data.buffer                     = buffer;
		data.bufferInfo.buffer          = buffer->Handle();
		data.bufferInfo.offset          = 0;
		data.bufferInfo.range           = info.size;

		m_Bindings.emplace(binding.binding, BindingData{ binding, 0, data });
	}

	void DescriptorBuffer::AddBinding(const VkDescriptorImageInfo& info, const VkDescriptorSetLayoutBinding& binding)
	{
		NEPTUNE_PROFILE_ZONE

		ImageBindingData data{};
		data.imageInfos.emplace_back(info);

		m_Bindings.emplace(binding.binding, BindingData{ binding, 0, data });
	}

	void DescriptorBuffer::UpdateBuffer(uint32_t binding, const void* data)
	{
		NEPTUNE_PROFILE_ZONE

		auto buffer = std::get<BufferBindingData>(m_Bindings[binding].data).buffer;

		buffer->WriteToBuffer(data);

		buffer->Flush();
	}

	void DescriptorBuffer::UpdateUniformTexture(uint32_t binding, const Vulkan::RenderTarget* renderTarget)
	{
		NEPTUNE_PROFILE_ZONE

		auto& imageInfos = std::get<ImageBindingData>(m_Bindings[binding].data).imageInfos;

		imageInfos[0].imageLayout       = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		imageInfos[0].imageView         = renderTarget->GetView();
		imageInfos[0].sampler           = renderTarget->GetSampler();

		UpdateDescriptorStagingBuffer(binding);
		
		UploadDescriptorStagingBuffer(binding);
	}
	
	void DescriptorBuffer::UpdateStorageTexture(uint32_t binding, const RenderTarget* renderTarget)
	{
		auto& imageInfos = std::get<ImageBindingData>(m_Bindings[binding].data).imageInfos;

		imageInfos[0].imageLayout       = VK_IMAGE_LAYOUT_GENERAL;
		imageInfos[0].imageView         = renderTarget->GetView();
		imageInfos[0].sampler           = renderTarget->GetSampler();

		UpdateDescriptorStagingBuffer(binding);
		
		UploadDescriptorStagingBuffer(binding);
	}

	void DescriptorBuffer::UpdateDynamicUniformBufferOffset(uint32_t offset)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Offset = offset;
	}
	
	void DescriptorBuffer::BuildDescriptorBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		CreateDescriptorSetLayout();

		vkGetDescriptorSetLayoutSizeEXT(GetContext().Get<IDevice>()->Handle(), m_Layout.GetHandle(), &m_LayoutSize);
		
		auto alignment = GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IDescriptorBuffer>()->GetProperties().descriptorBufferOffsetAlignment;
		m_LayoutSize = AlignUp(m_LayoutSize, alignment);
		
		for (const auto& binding : m_Bindings | std::views::keys)
		{
			vkGetDescriptorSetLayoutBindingOffsetEXT(GetContext().Get<IDevice>()->Handle(), m_Layout.GetHandle(), binding, &m_Bindings[binding].offset);
		}
		
		VkBufferCreateInfo                   stagingInfo{};
		stagingInfo.sType                  = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		stagingInfo.size                   = m_LayoutSize;
		stagingInfo.usage                  = VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT
						                   | VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT
						                   | VK_BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT
						                   | VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		stagingInfo.sharingMode            = VK_SHARING_MODE_EXCLUSIVE;
		
		m_StagingBuffer.CreateBuffer(stagingInfo, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		
		VkBufferCreateInfo                   createInfo{};
		createInfo.sType                   = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.size                    = m_LayoutSize;
		createInfo.usage                   = VK_BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT
							               | VK_BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT
							               | VK_BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT
							               | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
		createInfo.sharingMode             = VK_SHARING_MODE_EXCLUSIVE;
		
		m_DescriptorBuffer.CreateBuffer(createInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		
		m_DescriptorBuffer.SetName("DescriptorBuffer");
	}

	void DescriptorBuffer::UpdateDescriptorBuffer()
	{
		NEPTUNE_PROFILE_ZONE
		
		for (const auto& binding : m_Bindings | std::views::keys)
	    {
			UpdateDescriptorStagingBuffer(binding);
	    }
		
		CmdList2 cmdList(GetContext());

		cmdList.SetTransferCmdList();

		cmdList.Begin();

		VkBufferCopy                         region{};
		region.srcOffset                   = 0;
		region.dstOffset                   = 0;
		region.size                        = m_LayoutSize;

		cmdList.CmdCopyBuffer(m_StagingBuffer.Handle(), m_DescriptorBuffer.Handle(), region);

		cmdList.End();

		cmdList.SubmitWait();
	}

	void DescriptorBuffer::CreateDescriptorSetLayout()
	{
		NEPTUNE_PROFILE_ZONE

		std::vector<VkDescriptorSetLayoutBinding> setBindings{};
		std::vector<VkDescriptorBindingFlags> setBindingFlags{};

		for (const auto& binding : m_Bindings | std::views::values)
		{
			setBindings.emplace_back(binding.binding);

			switch (binding.binding.descriptorType)
			{
			case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
				setBindingFlags.emplace_back(VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT);
				break;
			case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
				setBindingFlags.emplace_back(VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT);
				break;
			default:
				setBindingFlags.emplace_back(VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT);
				break;
			}
		}

		VkDescriptorSetLayoutBindingFlagsCreateInfo         bindingFlags{};
		bindingFlags.sType                                = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
		bindingFlags.pNext                                = nullptr;
		bindingFlags.pBindingFlags                        = setBindingFlags.data();
		bindingFlags.bindingCount                         = static_cast<uint32_t>(setBindingFlags.size());

		VkDescriptorSetLayoutCreateInfo                     layoutCreateInfo{};
		layoutCreateInfo.sType                            = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutCreateInfo.bindingCount                     = static_cast<uint32_t>(setBindings.size());
		layoutCreateInfo.pBindings                        = setBindings.data();
		layoutCreateInfo.flags                            = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT | VK_DESCRIPTOR_SET_LAYOUT_CREATE_DESCRIPTOR_BUFFER_BIT_EXT;
		layoutCreateInfo.pNext                            = &bindingFlags;

		m_Layout.CreateDescriptorSetLayout(GetContext().Get<IDevice>()->Handle(), layoutCreateInfo);

		DEBUGUTILS_SETOBJECTNAME(m_Layout, "DescriptorSetLayout")
	}
	
	void DescriptorBuffer::UpdateDescriptorStagingBuffer(uint32_t binding) const
	{
		NEPTUNE_PROFILE_ZONE

		const auto mapped = m_StagingBuffer.Data();
		
		const auto& data = m_Bindings.at(binding);
		
        auto dst = static_cast<uint8_t*>(mapped) + data.offset;
		
        const auto& type = data.binding.descriptorType;
		
        for (uint32_t i = 0; i < data.binding.descriptorCount; ++i)
        {
            VkDescriptorGetInfoEXT              getInfo{};
	        getInfo.sType                     = VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT;
	        getInfo.type                      = type;
	        
            if (auto* p = std::get_if<BufferBindingData>(&data.data))
            {
	            VkDescriptorAddressInfoEXT      addrInfo{};
                addrInfo.sType                = VK_STRUCTURE_TYPE_DESCRIPTOR_ADDRESS_INFO_EXT;
                addrInfo.address              = p->buffer->GetDeviceAddress();
                addrInfo.range                = p->bufferInfo.range;
                addrInfo.format               = VK_FORMAT_UNDEFINED;

                if (type == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER || type == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC)
                {
	                getInfo.data.pUniformBuffer = &addrInfo;
                }
                else
                {
	                getInfo.data.pStorageBuffer = &addrInfo;
                }
            }
            else if (auto* p = std::get_if<ImageBindingData>(&data.data))
            {
                if (type == VK_DESCRIPTOR_TYPE_SAMPLER)
                {
	                getInfo.data.pSampler = &p->imageInfos[i].sampler;
                }
                else if (type == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
                {
	                getInfo.data.pCombinedImageSampler = &p->imageInfos[i];
                }
                else if (type == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE)
                {
	                getInfo.data.pSampledImage = &p->imageInfos[i];
                }
                else if (type == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
                {
	                getInfo.data.pStorageImage = &p->imageInfos[i];
                }
                else
                {
	                NEPTUNE_LOG_CORE(E) << "Unknown Descriptor Image Type.";
                }
            }
        	
        	auto descSize = GetBindingDescSize(type);

            vkGetDescriptorEXT(GetContext().Get<IDevice>()->Handle(), &getInfo, descSize, dst + i * descSize);
        }
	}
	
	void DescriptorBuffer::UploadDescriptorStagingBuffer(uint32_t binding) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const auto& data = m_Bindings.at(binding);
		
		const auto& type = data.binding.descriptorType;
		
		CmdList2 cmdList(GetContext());

		cmdList.SetTransferCmdList();

		cmdList.Begin();

		VkBufferCopy                         region{};
		region.srcOffset                   = data.offset;
		region.dstOffset                   = data.offset;
		region.size                        = GetBindingDescSize(type);

		cmdList.CmdCopyBuffer(m_StagingBuffer.Handle(), m_DescriptorBuffer.Handle(), region);

		cmdList.End();

		cmdList.SubmitWait();
	}

	uint64_t DescriptorBuffer::GetBindingDescSize(VkDescriptorType type) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const auto& props = GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IDescriptorBuffer>()->GetProperties();
		
		switch (type)
		{
			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:    return props.uniformBufferDescriptorSize;
			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:    return props.storageBufferDescriptorSize;
			case VK_DESCRIPTOR_TYPE_SAMPLER:                   return props.samplerDescriptorSize;
			case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:             return props.sampledImageDescriptorSize;
			case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:             return props.storageImageDescriptorSize;
			case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:          return props.inputAttachmentDescriptorSize;
			case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:    return props.combinedImageSamplerDescriptorSize;
			default:                                           return 0;
		}
	}
}

#endif