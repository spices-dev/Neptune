/**
* @file CmdList.cpp.
* @brief The CmdList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "CmdList.h"
#include "Data/Clock.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/CommandList.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/RenderPass.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/Buffer.h"
#include "Device/Graphics/Backend/Direct3D12/RHI/DescriptorList.h"
#include "Device/Graphics/Backend/Direct3D12/Resource/CommandList.h"

namespace Neptune::Direct3D12 {

	void CmdList::SetGraphicCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandList = GetContext().Get<IGraphicCommandList>()->IHandle(clock.m_FrameId);
	}

	void CmdList::SetComputeCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandList = GetContext().Get<IComputeCommandList>()->IHandle(clock.m_FrameId);
	}
	
	void* CmdList::GetCommandList() const
	{
		NEPTUNE_PROFILE_ZONE
		
		return m_CommandList->Handle();
	}

	void CmdList::CmdBeginRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass->BeginRenderPass(m_CommandList->Handle());
	}

	void CmdList::CmdEndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_RenderPass->EndPass(m_CommandList->Handle());
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
		
		m_CommandList->Handle()->DrawInstanced(vertexCount, instanceCount, firstVertex, firstInstance);
	}
	
	void CmdList::CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandList->Handle()->DrawIndexedInstanced(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
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
		
		m_CommandList->Handle()->Dispatch(groupCountX, groupCountY, groupCountZ);
	}
	
	void CmdList::CmdDispatchIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
	}
	
	void CmdList::CmdSetViewport(const glm::uvec2& viewPortSize) const
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