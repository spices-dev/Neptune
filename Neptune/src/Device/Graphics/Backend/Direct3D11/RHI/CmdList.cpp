/**
* @file CmdList.cpp.
* @brief The CmdList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "CmdList.h"
#include "Data/Clock.h"

namespace Neptune::Direct3D11 {

	void CmdList::SetGraphicCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE

		m_FrameIndex = clock.m_FrameIndex;
		m_ImageIndex = clock.m_ImageIndex;
	}

	void* CmdList::GetCommandList() const
	{
		NEPTUNE_PROFILE_ZONE
		
		return nullptr;
	}

	void CmdList::CmdBeginRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
	}

	void CmdList::CmdEndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
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
	
	void CmdList::CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE
		
	}
	
	void CmdList::CmdDrawInstance(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const
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
	}



}

#endif