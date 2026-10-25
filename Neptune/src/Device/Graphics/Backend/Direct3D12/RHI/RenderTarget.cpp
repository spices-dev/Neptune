/**
* @file RenderTarget.cpp.
* @brief The RenderTarget Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RenderTarget.h"
#include "Device/Graphics/Backend/Direct3D12/Converter.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/CmdList2.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/Buffer.h"

namespace Neptune::Direct3D12 {

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

		auto rhi = buffer->GetRHIImpl<Buffer>();

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
		
		//cmdList.CmdCopyImage(src, dst, { m_Texture->Width(), m_Texture->Height(), 1 });

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
			D3D12_RESOURCE_DESC             desc{};
			desc.Dimension                = ToD3D12ResourceDimension(info.domain);
			desc.Width                    = info.width;
			desc.Height                   = info.height;
			desc.DepthOrArraySize         = 1;
			desc.MipLevels                = 1;
			desc.Format                   = ToDXGIFormat(info.format);
			desc.SampleDesc.Count         = 1;
			desc.SampleDesc.Quality       = 0;
			desc.Layout                   = D3D12_TEXTURE_LAYOUT_UNKNOWN;
			desc.Flags                    = ToD3D12ResourceFlags(info.usage);
			
			m_Texture->CreateTexture(desc);
		}
		
		m_Texture->SetName("RenderTarget");
	}

	void RenderTarget::CreateDepthRenderTarget(const RenderTargetCreateInfo& info)
	{

	}
}

#endif