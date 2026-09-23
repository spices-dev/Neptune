/**
* @file CmdList.cpp.
* @brief The CmdList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "CmdList.h"
#include "Device/Graphics/Backend/WebGPU/RHI/RenderPass.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/CommandEncoder.h"
#include "Data/Clock.h"

namespace Neptune::WebGPU {

	void CmdList::SetGraphicCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE

		m_FrameIndex = clock.m_FrameIndex;
		m_ImageIndex = clock.m_ImageIndex;
		
		m_CommandEncoder = GetContext().Get<ICommandEncoder>()->IHandle(m_FrameIndex);
	}

	void CmdList::SetComputeCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_FrameIndex = clock.m_FrameIndex;
		m_ImageIndex = clock.m_ImageIndex;
	}
	
	void* CmdList::GetCommandList() const
	{
		NEPTUNE_PROFILE_ZONE
		
		return m_RenderPass->Handle();
	}

	void CmdList::CmdBeginRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass->BeginRenderPass(m_CommandEncoder.get());
	}

	void CmdList::CmdEndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass->EndRenderPass();
	}

	void CmdList::CmdBindDescriptor(const SP<RHI::DescriptorList>& descriptorList) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdBindPipeline(const SP<RHI::Pipeline>& pipeline)
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdBindIndexBuffer(const SP<RHI::IndexBuffer>& buffer) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void CmdList::CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void CmdList::CmdFillBuffer(const SP<RHI::Buffer>& buffer, uint64_t dstOffset, uint64_t size, uint32_t data) const
	{
		NEPTUNE_PROFILE_ZONE
	}
	
	void CmdList::CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void CmdList::CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void CmdList::CmdDrawIndexedIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
	}
	
	void CmdList::CmdDrawIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
	}
	
	void CmdList::CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdInsertBarrier(const SP<RHI::RenderTarget>& renderTarget, const Graphic::ImageBarrierDesc& desc) const
	{
		NEPTUNE_PROFILE_ZONE
	}
	
	void CmdList::CmdInsertBarrier(const Graphic::MemoryBarrierDesc& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void CmdList::CmdSetViewport(const glm::vec2& viewPortSize) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::SetRenderPass(const SP<RHI::RenderPass>& renderPass)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass = renderPass->GetRHIImpl<RenderPass>();
	}



}

#endif