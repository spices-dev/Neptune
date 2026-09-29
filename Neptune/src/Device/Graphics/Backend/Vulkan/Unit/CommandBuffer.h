/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::CommandBuffer Class.
	* This class defines the Vulkan::Unit::CommandBuffer behaves.
	*/
	class CommandBuffer : public Unit<VkCommandBuffer, VkObjectType::VK_OBJECT_TYPE_COMMAND_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandBuffer() = default;

		/**
		* @brief Destructor Function.
		*/
		~CommandBuffer() override;

		/**
		* @brief Create CommandBuffer.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkCommandBufferAllocateInfo.
		*/
		void CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info);

		/**
		* @brief Begin CommandBuffer.
		*
		* @param[in] info VkCommandBufferBeginInfo.
		*/
		void Begin(const VkCommandBufferBeginInfo& info) const;

		/**
		* @brief End CommandBuffer.
		*/
		void End() const;

		/**
		* @brief Begin RenderPass.
		*
		* @param[in] info VkRenderPassBeginInfo.
		* @param[in] content VkSubpassContents.
		*/
		void BeginRenderPass(const VkRenderPassBeginInfo& info, VkSubpassContents content) const;

		/**
		* @brief Begin Rendering.
		*
		* @param[in] info VkRenderingInfoKHR.
		*/
		void BeginRendering(const VkRenderingInfoKHR& info) const;
		
		/**
		* @brief End RenderPass.
		*/
		void EndRenderPass() const;

		/**
		* @brief End Rendering.
		*/
		void EndRendering() const;
		
		/**
		* @brief Bind Pipeline.
		* 
		* @param[in] bindPoint VkPipelineBindPoint.
		* @param[in] pipeline VkPipeline.
		*/
		void BindPipeline(VkPipelineBindPoint bindPoint, VkPipeline pipeline) const;

		/**
		* @brief Bind DescriptorSet.
		*
		* @param[in] bindPoint VkPipelineBindPoint.
		* @param[in] layout VkPipelineLayout.
		* @param[in] set .
		* @param[in] descriptorSet VkDescriptorSet.
		*/
		void BindDescriptorSet(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t set, VkDescriptorSet descriptorSet) const;

		/**
		* @brief Bind DescriptorSet with offset.
		*
		* @param[in] bindPoint VkPipelineBindPoint.
		* @param[in] layout VkPipelineLayout.
		* @param[in] set .
		* @param[in] descriptorSet VkDescriptorSet.
		* @param[in] offset Binding Offset.
		*/
		void BindDescriptorSet(VkPipelineBindPoint bindPoint, VkPipelineLayout layout, uint32_t set, VkDescriptorSet descriptorSet, uint32_t offset) const;
		
		/**
		* @brief Set Viewport.
		*
		* @param[in] viewport VkViewport.
		*/
		void SetViewport(const VkViewport& viewport) const;

		/**
		* @brief Set Scissor.
		*
		* @param[in] scissor VkRect2D.
		*/
		void SetScissor(const VkRect2D& scissor) const;

		/**
		* @brief Bind IndexBuffer.
		*
		* @param[in] buffer VkBuffer.
		* @param[in] offset VkDeviceSize.
		* @param[in] indexType VkIndexType.
		*/
		void BindIndexBuffer(VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) const;
		
		/**
		* @brief PushConstants.
		*
		* @param[in] layout VkPipelineLayout.
		* @param[in] data data.
		* @param[in] size size.
		* @param[in] offset offset.
		*/
		void PushConstants(VkPipelineLayout layout, const void* data, uint32_t size, uint32_t offset = 0) const;
		
		/**
		* @brief FillBuffer.
		*
		* @param[in] dstBuffer VkBuffer.
		* @param[in] dstOffset offset.
		* @param[in] size size.
		* @param[in] data data.
		*/
		void FillBuffer(VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) const;
		
		/**
		* @brief Draw.
		*
		* @param[in] vertexCount .
		* @param[in] instanceCount .
		* @param[in] firstVertex .
		* @param[in] firstInstance .
		*/
		void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const;

		/**
		* @brief DrawIndexed.
		*
		* @param[in] indexCount .
		* @param[in] instanceCount .
		* @param[in] firstIndex .
		* @param[in] vertexOffset .
		* @param[in] firstInstance .
		*/
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const;
		
		/**
		* @brief DrawIndexedIndirect.
		*
		* @param[in] buffer VkBuffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void DrawIndexedIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const;
		
		/**
		* @brief DrawIndexedIndirect2.
		*
		* @param[in] vkCmdDrawIndexedIndirect2KHR PFN_vkCmdDrawIndexedIndirect2KHR.
		* @param[in] info VkDrawIndirect2InfoKHR.
		*/
		void DrawIndexedIndirect2(PFN_vkCmdDrawIndexedIndirect2KHR vkCmdDrawIndexedIndirect2KHR, const VkDrawIndirect2InfoKHR& info) const;
		
		/**
		* @brief DrawIndexedIndirectCount.
		*
		* @param[in] buffer VkBuffer.
		* @param[in] offset .
		* @param[in] countBuffer .
		* @param[in] countBufferOffset .
		* @param[in] maxDrawCount .
		* @param[in] stride .
		*/
		void DrawIndexedIndirectCount(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
		
		/**
		* @brief DrawIndexedIndirectCount2.
		*
		* @param[in] vkCmdDrawIndexedIndirectCount2KHR PFN_vkCmdDrawIndexedIndirectCount2KHR.
		* @param[in] info VkDrawIndirectCount2InfoKHR.
		*/
		void DrawIndexedIndirectCount2(PFN_vkCmdDrawIndexedIndirectCount2KHR vkCmdDrawIndexedIndirectCount2KHR, const VkDrawIndirectCount2InfoKHR& info) const;
		
		/**
		* @brief DrawIndirect.
		*
		* @param[in] buffer VkBuffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void DrawIndirect(VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const;
		
		/**
		* @brief DrawIndirect2.
		*
		* @param[in] vkCmdDrawIndirect2KHR PFN_vkCmdDrawIndirect2KHR.
		* @param[in] info VkDrawIndirect2InfoKHR.
		*/
		void DrawIndirect2(PFN_vkCmdDrawIndirect2KHR vkCmdDrawIndirect2KHR, const VkDrawIndirect2InfoKHR& info) const;
		
		/**
		* @brief DrawIndirectCount.
		*
		* @param[in] buffer VkBuffer.
		* @param[in] offset .
		* @param[in] countBuffer VkBuffer.
		* @param[in] countBufferOffset .
		* @param[in] maxDrawCount .
		* @param[in] stride .
		*/
		void DrawIndirectCount(VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
		
		/**
		* @brief DrawIndirectCount2.
		*
		* @param[in] vkCmdDrawIndirectCount2KHR PFN_vkCmdDrawIndirectCount2KHR.
		* @param[in] info VkDrawIndirectCount2InfoKHR.
		*/
		void DrawIndirectCount2(PFN_vkCmdDrawIndirectCount2KHR vkCmdDrawIndirectCount2KHR, const VkDrawIndirectCount2InfoKHR& info) const;
		
		/**
		* @brief DrawIndirectByteCount.
		*
		* @param[in] vkCmdDrawIndirectByteCountEXT PFN_vkCmdDrawIndirectByteCountEXT.
		* @param[in] instanceCount .
		* @param[in] firstInstance .
		* @param[in] counterBuffer .
		* @param[in] counterBufferOffset .
		* @param[in] counterOffset .
		* @param[in] vertexStride .
		*/
		void DrawIndirectByteCount(PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) const;
		
		/**
		* @brief DrawIndirectByteCount2.
		*
		* @param[in] vkCmdDrawIndirectByteCount2EXT PFN_vkCmdDrawIndirectByteCount2EXT.
		* @param[in] instanceCount .
		* @param[in] firstInstance .
		* @param[in] info VkBindTransformFeedbackBuffer2InfoEXT.
		* @param[in] counterOffset .
		* @param[in] vertexStride .
		*/
		void DrawIndirectByteCount2(PFN_vkCmdDrawIndirectByteCount2EXT vkCmdDrawIndirectByteCount2EXT, uint32_t instanceCount, uint32_t firstInstance, const VkBindTransformFeedbackBuffer2InfoEXT& info, uint32_t counterOffset, uint32_t vertexStride) const;
		
		/**
		* @brief DrawMeshTasks.
		*
		* @param[in] vkCmdDrawMeshTasksEXT PFN_vkCmdDrawMeshTasksEXT.
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		void DrawMeshTasks(PFN_vkCmdDrawMeshTasksEXT vkCmdDrawMeshTasksEXT, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const;
		
		/**
		* @brief DrawMeshTasksIndirect.
		*
		* @param[in] vkCmdDrawMeshTasksIndirectEXT PFN_vkCmdDrawMeshTasksIndirectEXT.
		* @param[in] buffer VkBuffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void DrawMeshTasksIndirect(PFN_vkCmdDrawMeshTasksIndirectEXT vkCmdDrawMeshTasksIndirectEXT, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) const;
		
		/**
		* @brief DrawMeshTasksIndirect2.
		*
		* @param[in] vkCmdDrawMeshTasksIndirect2EXT PFN_vkCmdDrawMeshTasksIndirect2EXT.
		* @param[in] info VkDrawIndirect2InfoKHR.
		*/
		void DrawMeshTasksIndirect2(PFN_vkCmdDrawMeshTasksIndirect2EXT vkCmdDrawMeshTasksIndirect2EXT, const VkDrawIndirect2InfoKHR& info) const;
		
		/**
		* @brief DrawMeshTasksIndirectCount.
		*
		* @param[in] vkCmdDrawMeshTasksIndirectCountEXT PFN_vkCmdDrawMeshTasksIndirectCountEXT.
		* @param[in] buffer VkBuffer.
		* @param[in] offset .
		* @param[in] countBuffer VkBuffer.
		* @param[in] countBufferOffset .
		* @param[in] maxDrawCount .
		* @param[in] stride .
		*/
		void DrawMeshTasksIndirectCount(PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
		
		/**
		* @brief DrawMeshTasksIndirectCount2.
		*
		* @param[in] vkCmdDrawMeshTasksIndirectCount2EXT PFN_vkCmdDrawMeshTasksIndirectCount2EXT.
		* @param[in] info VkDrawIndirectCount2InfoKHR.
		*/
		void DrawMeshTasksIndirectCount2(PFN_vkCmdDrawMeshTasksIndirectCount2EXT vkCmdDrawMeshTasksIndirectCount2EXT, const VkDrawIndirectCount2InfoKHR& info) const;
		
		/**
		* @brief DrawMulti.
		*
		* @param[in] vkCmdDrawMultiEXT PFN_vkCmdDrawMultiEXT.
		* @param[in] drawCount .
		* @param[in] info VkMultiDrawInfoEXT.
		* @param[in] instanceCount .
		* @param[in] firstInstance .
		* @param[in] stride .
		*/
		void DrawMulti(PFN_vkCmdDrawMultiEXT vkCmdDrawMultiEXT, uint32_t drawCount, const VkMultiDrawInfoEXT& info, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) const;
		
		/**
		* @brief DrawMultiIndexed.
		*
		* @param[in] vkCmdDrawMultiIndexedEXT PFN_vkCmdDrawMultiIndexedEXT.
		* @param[in] drawCount .
		* @param[in] info VkMultiDrawInfoEXT.
		* @param[in] instanceCount .
		* @param[in] firstInstance .
		* @param[in] stride .
		* @param[in] vertexOffset .
		*/
		void DrawMultiIndexed(PFN_vkCmdDrawMultiIndexedEXT vkCmdDrawMultiIndexedEXT, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT& info, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* vertexOffset) const;
		
		/**
		* @brief DrawCluster.
		*
		* @param[in] vkCmdDrawClusterHUAWEI PFN_vkCmdDrawClusterHUAWEI.
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		void DrawCluster(PFN_vkCmdDrawClusterHUAWEI vkCmdDrawClusterHUAWEI, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const;
		
		/**
		* @brief DrawClusterIndirect.
		*
		* @param[in] vkCmdDrawClusterIndirectHUAWEI PFN_vkCmdDrawClusterIndirectHUAWEI.
		* @param[in] buffer VkBuffer.
		* @param[in] offset .
		*/
		void DrawClusterIndirect(PFN_vkCmdDrawClusterIndirectHUAWEI vkCmdDrawClusterIndirectHUAWEI, VkBuffer buffer, VkDeviceSize offset) const;
		
		/**
		* @brief Dispatch.
		* 
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		void Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const;
		
		/**
		* @brief DispatchIndirect2.
		* 
		* @param[in] info VkDispatchIndirect2InfoKHR.
		*/
		void DispatchIndirect2(const VkDispatchIndirect2InfoKHR& info) const;
		
		/**
		* @brief DispatchIndirect.
		* 
		* @param[in] buffer VkBuffer.
		* @param[in] offset VkDeviceSize.
		*/
		void DispatchIndirect(VkBuffer buffer, VkDeviceSize offset) const;
		
		/**
		* @brief Memory PipelineBarrier.
		* 
		* @param[in] srcStage VkPipelineStageFlags.
		* @param[in] dstStage VkPipelineStageFlags.
		* @param[in] flags VkDependencyFlags.
		* @param[in] barrier barrier.
		*/
		void CmdPipelineBarrier(VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, VkDependencyFlags flags, const VkMemoryBarrier& barrier) const;
		
		/**
		* @brief Buffer PipelineBarrier.
		* 
		* @param[in] srcStage VkPipelineStageFlags.
		* @param[in] dstStage VkPipelineStageFlags.
		* @param[in] flags VkDependencyFlags.
		* @param[in] barrier VkBufferMemoryBarrier.
		*/
		void CmdPipelineBarrier(VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, VkDependencyFlags flags, const VkBufferMemoryBarrier& barrier) const;
		
		/**
		* @brief Image PipelineBarrier.
		* 
		* @param[in] srcStage VkPipelineStageFlags.
		* @param[in] dstStage VkPipelineStageFlags.
		* @param[in] flags VkDependencyFlags.
		* @param[in] barrier VkImageMemoryBarrier.
		*/
		void CmdPipelineBarrier(VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, VkDependencyFlags flags, const VkImageMemoryBarrier& barrier) const;
		
		/**
		* @brief PipelineBarrier2.
		* 
		* @param[in] info VkDependencyInfo.
		*/
		void CmdPipelineBarrier2(const VkDependencyInfo& info) const;
		
		/**
		* @brief Begin VideoCoding.
		*
		* @param[in] fn PFN_vkCmdBeginVideoCodingKHR.
		* @param[in] info  VkVideoBeginCodingInfoKHR.
		*/
		void BeginVideoCoding(const PFN_vkCmdBeginVideoCodingKHR& fn, const VkVideoBeginCodingInfoKHR& info) const;

		/**
		* @brief Control VideoCoding.
		*
		* @param[in] fn PFN_vkCmdControlVideoCodingKHR.
		* @param[in] info VkVideoCodingControlInfoKHR.
		*/
		void ControlVideoCoding(const PFN_vkCmdControlVideoCodingKHR& fn, const VkVideoCodingControlInfoKHR& info) const;

		/**
		* @brief Decode Video.
		*
		* @param[in] fn PFN_vkCmdDecodeVideoKHR.
		* @param[in] info VkVideoDecodeInfoKHR.
		*/
		void DecodeVideo(const PFN_vkCmdDecodeVideoKHR& fn, const VkVideoDecodeInfoKHR& info) const;

		/**
		* @brief End Video Coding.
		*
		* @param[in] fn PFN_vkCmdEndVideoCodingKHR.
		* @param[in] info VkVideoEndCodingInfoKHR.
		*/
		void EndVideoCoding(const PFN_vkCmdEndVideoCodingKHR& fn, const VkVideoEndCodingInfoKHR& info) const;

		/**
		* @brief Optical Flow Execute.
		*
		* @param[in] fn PFN_vkCmdOpticalFlowExecuteNV.
		* @param[in] session VkOpticalFlowSessionNV.
		* @param[in] info VkOpticalFlowExecuteInfoNV.
		*/
		void OpticalFlowExecute(const PFN_vkCmdOpticalFlowExecuteNV& fn, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV& info) const;

		/**
		* @brief Copy Image.
		*
		* @param[in] src VkImage.
		* @param[in] dst VkImage.
		* @param[in] region VkImageCopy.
		*/
		void CopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const;

		/**
		* @brief Copy Buffer.
		*
		* @param[in] src VkBuffer.
		* @param[in] dst VkBuffer.
		* @param[in] region VkBufferCopy.
		*/
		void CopyBuffer(VkBuffer src, VkBuffer dst, const VkBufferCopy& region) const;

		/**
		* @brief Begin Query.
		*
		* @param[in] pool VkQueryPool.
		* @param[in] index .
		* @param[in] flag VkQueryControlFlags.
		*/
		void BeginQuery(VkQueryPool pool, uint32_t index, VkQueryControlFlags flag) const;

		/**
		* @brief End Query.
		*
		* @param[in] pool VkQueryPool.
		* @param[in] index .
		*/
		void EndQuery(VkQueryPool pool, uint32_t index) const;

		/**
		* @brief Write TimeStamp.
		*
		* @param[in] pool VkQueryPool.
		* @param[in] index .
		*/
		void WriteTimeStamp(VkQueryPool pool, uint32_t index) const;

		/**
		* @brief Reset TimeStamp.
		*
		* @param[in] pool VkQueryPool.
		* @param[in] count .
		*/
		void ResetQueryPool(VkQueryPool pool, uint32_t count) const;

	private:

		VkDevice m_Device           = VK_NULL_HANDLE;     // @brief VkDevice.
		VkCommandPool m_CommandPool = VK_NULL_HANDLE;     // @brief VkCommandPool.

	};
}

#endif