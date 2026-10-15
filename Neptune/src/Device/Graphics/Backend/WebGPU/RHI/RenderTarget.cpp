/**
* @file RenderTarget.cpp.
* @brief The RenderTarget Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "RenderTarget.h"
#include "Device/Graphics/Backend/WebGPU/Converter.h"
#include "Device/Graphics/Backend/WebGPU/RHI/CmdList2.h"
#include "Device/Graphics/Backend/WebGPU/RHI/Buffer.h"

namespace Neptune::WebGPU {

	void RenderTarget::CreateRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		CreateColorRenderTarget(info);
	}

	void* RenderTarget::CreateBindingID()
	{
		NEPTUNE_PROFILE_ZONE

		return nullptr;
	}

	bool RenderTarget::CopyToRenderTarget(const SP<RHI::RenderTarget>& target)
	{
		NEPTUNE_PROFILE_ZONE

		auto rhi = target->GetRHIImpl<RenderTarget>();

		return CopyToRenderTarget(rhi);
	}

	bool RenderTarget::CopyFromBuffer(const SP<RHI::Buffer>& buffer)
	{
		NEPTUNE_PROFILE_ZONE

		auto rhi = target->GetRHIImpl<Buffer>();

		return true;
	}
	
	void RenderTarget::SetName(const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Texture->SetName(name);
	}
	
	bool RenderTarget::CopyToRenderTarget(RenderTarget* target) const
	{
		NEPTUNE_PROFILE_ZONE

		CmdList2 cmdList(GetContext());

		cmdList.SetGraphicCmdList();

        cmdList.Begin();
		
		WGPUTexelCopyTextureInfo                        src{};
		src.texture                                   = m_Texture->Handle();
		src.mipLevel                                  = 0;
		src.origin                                    = { m_Texture->Width(), m_Texture->Height(), 1 };
		src.aspect                                    = WGPUTextureAspect_All;

		WGPUTexelCopyTextureInfo                        dst{};
		dst.texture                                   = target->Handle();
		dst.mipLevel                                  = 0;
		dst.origin                                    = { target->m_Texture->Width(), target->m_Texture->Height(), 1 };
		dst.aspect                                    = WGPUTextureAspect_All;
		
		cmdList.CmdCopyImage(src, dst, { m_Texture->Width(), m_Texture->Height(), 1 });

        cmdList.End();

        cmdList.SubmitWait();

		return true;
	}

	TextureFormat RenderTarget::GetFormat() const
	{
		NEPTUNE_PROFILE_ZONE

		return ToTextureFormat(m_Texture->GetFormat());
	}

	void RenderTarget::CreateColorRenderTarget(const RenderTargetCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_Texture = CreateSP<Resource::Texture>(GetContext());

		{
			WGPUTextureFormat format                         = ToWGPUTextureFormat(info.format);
			
			WGPUTextureDescriptor                              desc{};
			desc.dimension                                   = ToWGPUTextureDimension(info.domain);
			desc.size                                        = { info.width, info.height, 1 };
			desc.format                                      = format;
			desc.mipLevelCount                               = 1;
			desc.sampleCount                                 = 1;
			desc.viewFormatCount                             = 1;
			desc.viewFormats                                 = &format;
			desc.usage                                       = ToWGPUTextureUsage(info.usage); 

			m_Texture->CreateTexture(desc);
		}
		
		{
			WGPUTextureViewDescriptor                          desc{};
			desc.dimension                                   = ToWGPUTextureViewDimension(info.domain);
			desc.format                                      = ToWGPUTextureFormat(info.format);
			desc.baseMipLevel                                = 0;
			desc.mipLevelCount                               = 1;
			desc.baseArrayLayer                              = 0;
			desc.arrayLayerCount                             = 1;
			desc.aspect                                      = WGPUTextureAspect_All;
			desc.usage                                       = ToWGPUTextureUsage(info.usage); 

			m_Texture->CreateTextureView(desc);
		}

		{
			WGPUSamplerDescriptor                              desc{};
			desc.magFilter                                   = WGPUFilterMode_Linear;
			desc.minFilter                                   = WGPUFilterMode_Linear;
			desc.addressModeU                                = WGPUAddressMode_Repeat;
			desc.addressModeV                                = WGPUAddressMode_Repeat;
			desc.addressModeW                                = WGPUAddressMode_Repeat;
			desc.mipmapFilter                                = WGPUMipmapFilterMode_Linear;
			desc.lodMinClamp                                 = 0.0f;
			desc.lodMaxClamp                                 = 1000.0f;
			desc.compare                                     = WGPUCompareFunction_Always;
			desc.maxAnisotropy                               = 1;

			m_Texture->CreateSampler(desc);
		}

		m_Texture->SetName("RenderTarget");
	}

	void RenderTarget::CreateDepthRenderTarget(const RenderTargetCreateInfo& info)
	{

	}
}

#endif