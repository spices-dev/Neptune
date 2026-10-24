/**
* @file RenderPass.cpp.
* @brief The RenderPass Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RenderPass.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/Pipeline.h"

namespace Neptune::Direct3D12 {

	void RenderPass::AddSwapChainAttachment()
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void RenderPass::AddColorAttachment(const SP<RHI::RenderTarget>& renderTarget, const RenderTargetAttachmentInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

	}

	void RenderPass::BeginRenderPass(const Unit::CommandEncoder* commandEncoder)
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void RenderPass::BeginComputePass(const Unit::CommandEncoder* commandEncoder)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void RenderPass::EndPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void RenderPass::BindPipeline(const SP<RHI::Pipeline>& pipeline) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void RenderPass::BindDescriptorList(const DescriptorList* descriptorList) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void RenderPass::UpdateShaderConstant(const void* data, uint32_t size, uint32_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
}

#endif