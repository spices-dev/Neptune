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

	bool RenderTarget::CopyToRenderTarget(RenderTarget* target) const
	{
		NEPTUNE_PROFILE_ZONE

		

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

		
	}

	void RenderTarget::CreateDepthRenderTarget(const RenderTargetCreateInfo& info)
	{

	}
}

#endif