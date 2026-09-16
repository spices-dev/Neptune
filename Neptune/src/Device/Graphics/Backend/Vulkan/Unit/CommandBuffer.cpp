/**
* @file CommandBuffer.cpp.
* @brief The CommandBuffer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CommandBuffer.h"

#include <functional>

namespace Neptune::Vulkan::Unit {

	CommandBuffer::~CommandBuffer()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		vkFreeCommandBuffers(m_Device, m_CommandPool, 1, &m_Handle);
	}

	void CommandBuffer::CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		NEPTUNE_ASSERT(device && info.commandPool)

		m_Device = device;
		m_CommandPool = info.commandPool;

		VULKAN_CHECK(vkAllocateCommandBuffers(m_Device, &info, &m_Handle))
	}

	void CommandBuffer::Begin(const VkCommandBufferBeginInfo& info) const
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(vkBeginCommandBuffer(m_Handle, &info))
	}

	void CommandBuffer::End() const
	{
		NEPTUNE_PROFILE_ZONE

		VULKAN_CHECK(vkEndCommandBuffer(m_Handle))
	}

	void CommandBuffer::BeginRenderPass(const VkRenderPassBeginInfo& info, VkSubpassContents content) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBeginRenderPass(m_Handle, &info, content);
	}
	
	void CommandBuffer::BeginRendering(const VkRenderingInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdBeginRendering(m_Handle, &info);
	}

	void CommandBuffer::EndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdEndRenderPass(m_Handle);
	}

	void CommandBuffer::EndRendering() const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdEndRendering(m_Handle);
	}
	
	void CommandBuffer::BindPipeline(VkPipelineBindPoint bindPoint, VkPipeline pipeline) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBindPipeline(m_Handle, bindPoint, pipeline);
	}

	void CommandBuffer::BindDescriptorSet(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t set, VkDescriptorSet descriptorSet) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBindDescriptorSets(m_Handle, bindPoint, layout, set, 1, &descriptorSet, 0, nullptr);
	}
	
	void CommandBuffer::BindDescriptorSet(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t set, VkDescriptorSet descriptorSet, uint32_t offset) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBindDescriptorSets(m_Handle, bindPoint, layout, set, 1, &descriptorSet, 1, &offset);
	}

	void CommandBuffer::SetViewport(const VkViewport& viewport) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdSetViewport(m_Handle, 0, 1, &viewport);
	}

	void CommandBuffer::SetScissor(const VkRect2D& scissor) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdSetScissor(m_Handle, 0, 1, &scissor);
	}
	
	void CommandBuffer::BindIndexBuffer(VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdBindIndexBuffer(m_Handle, buffer, offset, indexType);
	}

	void CommandBuffer::PushConstants(VkPipelineLayout layout, const void* data, uint32_t size, uint32_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdPushConstants(m_Handle, layout, VK_SHADER_STAGE_ALL, offset, size, data);
	}
	
	void CommandBuffer::FillBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdFillBuffer(m_Handle, dstBuffer, dstOffset, size, data);
	}
	
	void CommandBuffer::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdDraw(m_Handle, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void CommandBuffer::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndexed(m_Handle, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
	}
	
	void CommandBuffer::DrawIndexedIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndexedIndirect(m_Handle, buffer, offset, drawCount, stride);
	}
	
	void CommandBuffer::DrawIndexedIndirect2(PFN_vkCmdDrawIndexedIndirect2KHR vkCmdDrawIndexedIndirect2KHR, const VkDrawIndirect2InfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndexedIndirect2KHR(m_Handle, &info);
	}
	
	void CommandBuffer::DrawIndexedIndirectCount(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndexedIndirectCount(m_Handle, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
	}
	
	void CommandBuffer::DrawIndexedIndirectCount2(PFN_vkCmdDrawIndexedIndirectCount2KHR vkCmdDrawIndexedIndirectCount2KHR, const VkDrawIndirectCount2InfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndexedIndirectCount2KHR(m_Handle, &info);
	}
	
	void CommandBuffer::DrawIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndirect(m_Handle, buffer, offset, drawCount, stride);
	}
	
	void CommandBuffer::DrawIndirect2(PFN_vkCmdDrawIndirect2KHR vkCmdDrawIndirect2KHR, const VkDrawIndirect2InfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndirect2KHR(m_Handle, &info);
	}
	
	void CommandBuffer::DrawIndirectCount(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndirectCount(m_Handle, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
	}
	
	void CommandBuffer::DrawIndirectCount2(PFN_vkCmdDrawIndirectCount2KHR vkCmdDrawIndirectCount2KHR, const VkDrawIndirectCount2InfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndirectCount2KHR(m_Handle, &info);
	}
	
	void CommandBuffer::DrawIndirectByteCount(PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndirectByteCountEXT(m_Handle, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
	}
	
	void CommandBuffer::DrawIndirectByteCount2(PFN_vkCmdDrawIndirectByteCount2EXT vkCmdDrawIndirectByteCount2EXT, uint32_t instanceCount, uint32_t firstInstance, const VkBindTransformFeedbackBuffer2InfoEXT& info, uint32_t counterOffset, uint32_t vertexStride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawIndirectByteCount2EXT(m_Handle, instanceCount, firstInstance, &info, counterOffset, vertexStride);
	}
	
	void CommandBuffer::DrawMeshTasks(PFN_vkCmdDrawMeshTasksEXT vkCmdDrawMeshTasksEXT, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawMeshTasksEXT(m_Handle, groupCountX, groupCountY, groupCountZ);
	}
	
	void CommandBuffer::DrawMeshTasksIndirect(PFN_vkCmdDrawMeshTasksIndirectEXT vkCmdDrawMeshTasksIndirectEXT, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawMeshTasksIndirectEXT(m_Handle, buffer, offset, drawCount, stride);
	}
	
	void CommandBuffer::DrawMeshTasksIndirect2(PFN_vkCmdDrawMeshTasksIndirect2EXT vkCmdDrawMeshTasksIndirect2EXT, const VkDrawIndirect2InfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawMeshTasksIndirect2EXT(m_Handle, &info);
	}
	
	void CommandBuffer::DrawMeshTasksIndirectCount(PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawMeshTasksIndirectCountEXT(m_Handle, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
	}
	
	void CommandBuffer::DrawMeshTasksIndirectCount2(PFN_vkCmdDrawMeshTasksIndirectCount2EXT vkCmdDrawMeshTasksIndirectCount2EXT, const VkDrawIndirectCount2InfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawMeshTasksIndirectCount2EXT(m_Handle, &info);
	}
	
	void CommandBuffer::DrawMulti(PFN_vkCmdDrawMultiEXT vkCmdDrawMultiEXT, uint32_t drawCount, const VkMultiDrawInfoEXT& info, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawMultiEXT(m_Handle, drawCount, &info, instanceCount, firstInstance, stride);
	}
	
	void CommandBuffer::DrawMultiIndexed(PFN_vkCmdDrawMultiIndexedEXT vkCmdDrawMultiIndexedEXT, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT& info, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* vertexOffset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawMultiIndexedEXT(m_Handle, drawCount, &info, instanceCount, firstInstance, stride, vertexOffset);
	}
	
	void CommandBuffer::DrawCluster(PFN_vkCmdDrawClusterHUAWEI vkCmdDrawClusterHUAWEI, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawClusterHUAWEI(m_Handle, groupCountX, groupCountY, groupCountZ);
	}
	
	void CommandBuffer::DrawClusterIndirect(PFN_vkCmdDrawClusterIndirectHUAWEI vkCmdDrawClusterIndirectHUAWEI, VkBuffer buffer, VkDeviceSize offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDrawClusterIndirectHUAWEI(m_Handle, buffer, offset);
	}
	
	void CommandBuffer::Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdDispatch(m_Handle, groupCountX, groupCountY, groupCountZ);
	}
	
	void CommandBuffer::CmdPipelineBarrier(VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, VkDependencyFlags flags, const VkMemoryBarrier& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdPipelineBarrier(m_Handle, srcStage, dstStage, flags, 1, &barrier, 0, nullptr, 0, nullptr);
	}
	
	void CommandBuffer::CmdPipelineBarrier(VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, VkDependencyFlags flags, const VkBufferMemoryBarrier& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdPipelineBarrier(m_Handle, srcStage, dstStage, flags, 0, nullptr, 1, &barrier, 0, nullptr);
	}
	
	void CommandBuffer::CmdPipelineBarrier(VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, VkDependencyFlags flags, const VkImageMemoryBarrier& barrier) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdPipelineBarrier(m_Handle, srcStage, dstStage, flags, 0, nullptr, 0, nullptr, 1, &barrier);
	}
	
	void CommandBuffer::CmdPipelineBarrier2(const VkDependencyInfo& info) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdPipelineBarrier2(m_Handle, &info);
	}
	
	void CommandBuffer::BeginVideoCoding(const PFN_vkCmdBeginVideoCodingKHR& fn, const VkVideoBeginCodingInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, &info);
	}

	void CommandBuffer::ControlVideoCoding(const PFN_vkCmdControlVideoCodingKHR& fn, const VkVideoCodingControlInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, &info);
	}

	void CommandBuffer::DecodeVideo(const PFN_vkCmdDecodeVideoKHR& fn, const VkVideoDecodeInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, &info);
	}

	void CommandBuffer::EndVideoCoding(const PFN_vkCmdEndVideoCodingKHR& fn, const VkVideoEndCodingInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, &info);
	}

	void CommandBuffer::OpticalFlowExecute(const PFN_vkCmdOpticalFlowExecuteNV& fn, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV& info) const
	{
		NEPTUNE_PROFILE_ZONE

		std::invoke(fn, m_Handle, session, &info);
	}

	void CommandBuffer::CopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdCopyImage(m_Handle, src, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
	}
	
	void CommandBuffer::CopyBuffer(VkBuffer src, VkBuffer dst, const VkBufferCopy& region) const
	{
		NEPTUNE_PROFILE_ZONE
		
		vkCmdCopyBuffer(m_Handle, src, dst, 1, &region);
	}

	void CommandBuffer::BeginQuery(VkQueryPool pool, uint32_t index, VkQueryControlFlags flag) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdBeginQuery(m_Handle, pool, index, flag);
	}

	void CommandBuffer::EndQuery(VkQueryPool pool, uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdEndQuery(m_Handle, pool, index);
	}

	void CommandBuffer::WriteTimeStamp(VkQueryPool pool, uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdWriteTimestamp2(m_Handle, VK_PIPELINE_STAGE_2_NONE, pool, index);
	}

	void CommandBuffer::ResetQueryPool(VkQueryPool pool, uint32_t count) const
	{
		NEPTUNE_PROFILE_ZONE

		vkCmdResetQueryPool(m_Handle, pool, 0, count);
	}
}

#endif