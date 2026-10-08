#include "Pchheader.h"
#include "RenderTarget.h"
#include "Device/Graphics/Frontend/RHI/RenderTarget.h"

namespace Neptune {

	RenderTarget::RenderTarget()
	{
		m_RHIResource = CreateSP<RHI::RenderTarget>();

		m_RHIResource->CreateRenderTarget({});
	}

	RenderTarget::RenderTarget(const RenderTargetCreateInfo& info)
	{
		m_RHIResource = CreateSP<RHI::RenderTarget>();

		m_RHIResource->CreateRenderTarget(info);
	}

	void RenderTarget::SetName(const std::string& name)
	{
		m_Name = name;
		
		m_RHIResource->SetName(name);
	}

	bool RenderTarget::CopyToRenderTarget(const SP<RenderTarget>& target) const
	{
		return m_RHIResource->CopyToRenderTarget(target->GetRHIResource());
	}
}