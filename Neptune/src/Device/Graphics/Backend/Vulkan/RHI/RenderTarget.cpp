/**
* @file RenderTarget.cpp.
* @brief The RenderTarget Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderTarget.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"
#include "Device/Graphics/Backend/Vulkan/RHI/CmdList2.h"

namespace Neptune::Vulkan {
	
	RenderTarget::RenderTarget(Context& context)
		: ContextAccessor(context)
		, m_DescriptorSet(context)
		, m_ImageLayout(Middleware::IImageLayout::Create(context))
	{}

	void RenderTarget::CreateRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		CreateColorRenderTarget(info);
	}

	void* RenderTarget::CreateBindingID()
	{
		NEPTUNE_PROFILE_ZONE

		VkDescriptorImageInfo                               imageInfo{};
		imageInfo.imageLayout                             = m_ImageLayout->From(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
		imageInfo.imageView                               = m_Image->GetView();
		imageInfo.sampler                                 = m_Image->GetSampler();

		VkDescriptorSetLayoutBinding                        layoutBinding{};
		layoutBinding.binding                             = 0;
		layoutBinding.descriptorType                      = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
		layoutBinding.descriptorCount                     = 1;
		layoutBinding.stageFlags                          = VK_SHADER_STAGE_FRAGMENT_BIT;

		m_DescriptorSet.AddBinding(imageInfo, layoutBinding);

		m_DescriptorSet.BuildDescriptorSet();

		m_DescriptorSet.UpdateDescriptorSet();

		return m_DescriptorSet.Handle();
	}

	bool RenderTarget::CopyToRenderTarget(const SP<RHI::RenderTarget>& target)
	{
		NEPTUNE_PROFILE_ZONE

		auto rhi = target->GetRHIImpl<RenderTarget>();

		return CopyToRenderTarget(rhi);
	}

	void RenderTarget::SetName(const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Image->SetName(name);
	}

	bool RenderTarget::CopyToRenderTarget(RenderTarget* target) const
	{
		NEPTUNE_PROFILE_ZONE

		CmdList2 cmdList(GetContext());

		cmdList.SetGraphicCmdList();

        cmdList.Begin();

		if (m_Image->GetFormat() == VK_FORMAT_G8_B8R8_2PLANE_420_UNORM)
		{
			VkImageCopy                                     region{};
            region.srcSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_0_BIT;
            region.srcSubresource.layerCount              = m_Image->GetLayerCount();
            region.srcSubresource.baseArrayLayer          = 0;
            region.srcSubresource.mipLevel                = 0;
            region.dstSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_0_BIT;
            region.dstSubresource.layerCount              = target->m_Image->GetLayerCount();
            region.dstSubresource.baseArrayLayer          = 0;
            region.dstSubresource.mipLevel                = 0;
            region.extent.width                           = m_Image->Width();
            region.extent.height                          = m_Image->Height();
            region.extent.depth                           = 1;

			{
				Graphic::ImageBarrierDesc           desc{};
				desc.memoryDesc.srcAccess         = Graphic::EPipelineAccess::ShaderRead;
				desc.memoryDesc.dstAccess         = Graphic::EPipelineAccess::TransferRead;
				desc.memoryDesc.srcStage          = Graphic::EPipelineStage::FragmentShader;
				desc.memoryDesc.dstStage          = Graphic::EPipelineStage::Transfer;
				desc.srcLayout                    = Graphic::EImageLayout::ShaderRead;
				desc.dstLayout                    = Graphic::EImageLayout::TransferSrc;
            
				cmdList.CmdInsertBarrier(m_Image->Handle(), desc);
			}

			{
				Graphic::ImageBarrierDesc           desc{};
				desc.memoryDesc.srcAccess         = Graphic::EPipelineAccess::ShaderRead;
				desc.memoryDesc.dstAccess         = Graphic::EPipelineAccess::TransferWrite;
				desc.memoryDesc.srcStage          = Graphic::EPipelineStage::FragmentShader;
				desc.memoryDesc.dstStage          = Graphic::EPipelineStage::Transfer;
				desc.srcLayout                    = Graphic::EImageLayout::ShaderRead;
				desc.dstLayout                    = Graphic::EImageLayout::TransferDst;
				
				cmdList.CmdInsertBarrier(target->Handle(), desc);
			}

            cmdList.CmdCopyImage(Handle(), target->Handle(), region);

            region.srcSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_1_BIT;
            region.dstSubresource.aspectMask              = VK_IMAGE_ASPECT_PLANE_1_BIT;
            region.extent.width                           = m_Image->Width() / 2;
            region.extent.height                          = m_Image->Height() / 2;

            cmdList.CmdCopyImage(Handle(), target->Handle(), region);

			{
				Graphic::ImageBarrierDesc           desc{};
				desc.memoryDesc.srcAccess         = Graphic::EPipelineAccess::TransferRead;
				desc.memoryDesc.dstAccess         = Graphic::EPipelineAccess::ShaderRead;
				desc.memoryDesc.srcStage          = Graphic::EPipelineStage::Transfer;
				desc.memoryDesc.dstStage          = Graphic::EPipelineStage::FragmentShader;
				desc.srcLayout                    = Graphic::EImageLayout::TransferSrc;
				desc.dstLayout                    = Graphic::EImageLayout::ShaderRead;
            
				cmdList.CmdInsertBarrier(m_Image->Handle(), desc);
			}

			{
				Graphic::ImageBarrierDesc           desc{};
				desc.memoryDesc.srcAccess         = Graphic::EPipelineAccess::TransferWrite;
				desc.memoryDesc.dstAccess         = Graphic::EPipelineAccess::ShaderRead;
				desc.memoryDesc.srcStage          = Graphic::EPipelineStage::Transfer;
				desc.memoryDesc.dstStage          = Graphic::EPipelineStage::FragmentShader;
				desc.srcLayout                    = Graphic::EImageLayout::TransferDst;
				desc.dstLayout                    = Graphic::EImageLayout::ShaderRead;
            
				cmdList.CmdInsertBarrier(target->Handle(), desc);
			}
		}
		else
		{
			VkImageCopy                                     region{};
			region.srcSubresource.aspectMask              = VK_IMAGE_ASPECT_COLOR_BIT;
			region.srcSubresource.layerCount              = m_Image->GetLayerCount();
			region.srcSubresource.baseArrayLayer          = 0;
			region.srcSubresource.mipLevel                = 0;
			region.dstSubresource.aspectMask              = VK_IMAGE_ASPECT_COLOR_BIT;
			region.dstSubresource.layerCount              = target->m_Image->GetLayerCount();
			region.dstSubresource.baseArrayLayer          = 0;
			region.dstSubresource.mipLevel                = 0;
			region.extent.width                           = m_Image->Width();
			region.extent.height                          = m_Image->Height();
			region.extent.depth                           = 1;

			{
				Graphic::ImageBarrierDesc           desc{};
				desc.memoryDesc.srcAccess         = Graphic::EPipelineAccess::ShaderRead;
				desc.memoryDesc.dstAccess         = Graphic::EPipelineAccess::TransferWrite;
				desc.memoryDesc.srcStage          = Graphic::EPipelineStage::FragmentShader;
				desc.memoryDesc.dstStage          = Graphic::EPipelineStage::Transfer;
				desc.srcLayout                    = Graphic::EImageLayout::ShaderRead;
				desc.dstLayout                    = Graphic::EImageLayout::TransferDst;
				
				cmdList.CmdInsertBarrier(target->Handle(), desc);
			}

			cmdList.CmdCopyImage(Handle(), target->Handle(), region);

			{
				Graphic::ImageBarrierDesc           desc{};
				desc.memoryDesc.srcAccess         = Graphic::EPipelineAccess::TransferWrite;
				desc.memoryDesc.dstAccess         = Graphic::EPipelineAccess::ShaderRead;
				desc.memoryDesc.srcStage          = Graphic::EPipelineStage::Transfer;
				desc.memoryDesc.dstStage          = Graphic::EPipelineStage::FragmentShader;
				desc.srcLayout                    = Graphic::EImageLayout::TransferDst;
				desc.dstLayout                    = Graphic::EImageLayout::ShaderRead;
            
				cmdList.CmdInsertBarrier(target->Handle(), desc);
			}
		}

        cmdList.End();

        cmdList.SubmitWait();

		return true;
	}

	TextureFormat RenderTarget::GetFormat() const
	{
		NEPTUNE_PROFILE_ZONE

		return ToTextureFormat(m_Image->GetFormat());
	}

	void RenderTarget::CreateColorRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_Image = CreateSP<Resource::Image>(GetContext());

		{
			VkImageCreateInfo                                  createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			createInfo.imageType                             = ToVkImageType(info.domain);
			createInfo.extent.width                          = info.width;
			createInfo.extent.height                         = info.height;
			createInfo.extent.depth                          = 1;
			createInfo.mipLevels                             = 1;
			createInfo.arrayLayers                           = 1;
			createInfo.format                                = ToVkFormat(info.format);
			createInfo.tiling                                = VK_IMAGE_TILING_OPTIMAL;
			createInfo.initialLayout                         = VK_IMAGE_LAYOUT_UNDEFINED;
			createInfo.usage                                 = ToVkImageUsageFlags(info.usage); 
			createInfo.sharingMode                           = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.samples                               = VK_SAMPLE_COUNT_1_BIT;
			createInfo.flags                                 = 0;

			m_Image->CreateImage(createInfo, ToVkMemoryPropertyFlags(info.memoryUsage));
			
			CmdList2 cmdList(GetContext());
			
			cmdList.SetGraphicCmdList();
			
			cmdList.Begin();
			
			Graphic::ImageBarrierDesc           desc{};
			desc.memoryDesc.srcAccess         = Graphic::EPipelineAccess::None;
			desc.memoryDesc.dstAccess         = Graphic::EPipelineAccess::None;
			desc.memoryDesc.srcStage          = Graphic::EPipelineStage::TopPipeline;
			desc.memoryDesc.dstStage          = Graphic::EPipelineStage::TopPipeline;
			desc.srcLayout                    = Graphic::EImageLayout::Undefined;
			desc.dstLayout                    = Graphic::EImageLayout::General;
			
			cmdList.CmdInsertBarrier(m_Image->Handle(), desc);
			
			cmdList.End();
			
			cmdList.SubmitWait();
		}
		
		{
			VkImageViewCreateInfo                              createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image                                 = m_Image->Handle();

			createInfo.viewType                              = ToVkImageViewType(info.domain);
			createInfo.format                                = ToVkFormat(info.format);
												       	  
			createInfo.components.r                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a                          = VK_COMPONENT_SWIZZLE_IDENTITY;
												       	  
			createInfo.subresourceRange.aspectMask           = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel         = 0;
			createInfo.subresourceRange.levelCount           = 1;
			createInfo.subresourceRange.baseArrayLayer       = 0;
			createInfo.subresourceRange.layerCount           = 1;

			m_Image->CreateImageView(createInfo);
		}

		{
			const auto& properties = GetContext().Get<IPhysicalDevice>()->GetProperties();
			
			VkSamplerCreateInfo                                createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			createInfo.magFilter                             = VK_FILTER_LINEAR;
			createInfo.minFilter                             = VK_FILTER_LINEAR;
			createInfo.addressModeU                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.addressModeV                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.addressModeW                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.anisotropyEnable                      = VK_TRUE;
			createInfo.maxAnisotropy                         = properties.limits.maxSamplerAnisotropy;
			createInfo.borderColor                           = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			createInfo.unnormalizedCoordinates               = VK_FALSE;
			createInfo.compareEnable                         = VK_FALSE;
			createInfo.compareOp                             = VK_COMPARE_OP_ALWAYS;
													         
			createInfo.mipmapMode                            = VK_SAMPLER_MIPMAP_MODE_LINEAR;
			createInfo.mipLodBias                            = 0.0f;
			createInfo.minLod                                = 0;
			createInfo.maxLod                                = VK_LOD_CLAMP_NONE;

			m_Image->CreateSampler(createInfo);
		}

		m_Image->SetName("RenderTarget");
	}

	void RenderTarget::CreateDepthRenderTarget(const RenderTargetCreateInfo& info)
	{

	}
}

#endif