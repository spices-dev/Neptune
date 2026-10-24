/**
* @file CmdList.cpp.
* @brief The CmdList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CmdList.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/CommandBuffer.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/RHI/Pipeline.h"
#include "Device/Graphics/Backend/Vulkan/RHI/DescriptorList.h"
#include "Device/Graphics/Backend/Vulkan/RHI/IndexBuffer.h"
#include "Device/Graphics/Backend/Vulkan/RHI/Buffer.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/Vulkan/Resource/QueryPool.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"
#include "Data/Clock.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"
#include "Device/Graphics/Frontend/RHI/Buffer.h"

namespace Neptune::Vulkan {
	
	CmdList::CmdList(Context& context)
		: ContextAccessor(context)
		, m_Synchronization(Middleware::ISynchronization::Create(context))
		, m_Indirect(Middleware::IIndirect::Create(context))
		, m_ImageLayout(Middleware::IImageLayout::Create(context))
	{}

	void CmdList::SetGraphicCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE

		m_ImageIndex = clock.m_ImageIndex;

		m_CommandBuffer = GetContext().Get<IGraphicCommandBuffer>()->IHandle(clock.m_FrameId);

		m_BindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	}
	
	void CmdList::SetComputeCmdList(const Data::Clock& clock)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_ImageIndex = clock.m_ImageIndex;

		m_CommandBuffer = GetContext().Get<IComputeCommandBuffer>()->IHandle(clock.m_FrameId);

		m_BindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;
	}

	void* CmdList::GetCommandList() const
	{
		NEPTUNE_PROFILE_ZONE

		return m_CommandBuffer->GetHandle();
	}

	void CmdList::CmdBeginRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass->BeginRenderPass(m_CommandBuffer.get(), m_ImageIndex);
	}

	void CmdList::CmdEndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass->EndRenderPass(m_CommandBuffer.get());
	}

	void CmdList::CmdBindDescriptor(const SP<RHI::DescriptorList>& descriptorList) const
	{
		NEPTUNE_PROFILE_ZONE

		auto sharedRhi = dynamic_cast<const DescriptorList*>(descriptorList->GetSharedImpl());

		auto rhi = descriptorList->GetRHIImpl<DescriptorList>();

		for (const auto& [fst, snd] : sharedRhi->GetSets())
		{
			m_CommandBuffer->BindDescriptorSet(m_BindPoint, m_PipelineLayout, fst, snd->Handle());
		}

		for (const auto& [fst, snd] : rhi->GetSets())
		{
			if (snd->GetOffset())
			{
				m_CommandBuffer->BindDescriptorSet(m_BindPoint, m_PipelineLayout, fst, snd->Handle(), *snd->GetOffset());
			}
			else
			{
				m_CommandBuffer->BindDescriptorSet(m_BindPoint, m_PipelineLayout, fst, snd->Handle());
			}
		}
	}

	void CmdList::CmdBindPipeline(const SP<RHI::Pipeline>& pipeline)
	{
		NEPTUNE_PROFILE_ZONE

		auto rhi = pipeline->GetRHIImpl<Pipeline>();

		assert(rhi->GetBindPoint() == m_BindPoint);

		m_PipelineLayout = rhi->GetPipelineLayout();

		m_CommandBuffer->BindPipeline(rhi->GetBindPoint(), rhi->Handle());
	}

	void CmdList::CmdBindIndexBuffer(const SP<RHI::IndexBuffer>& buffer) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandBuffer->BindIndexBuffer(buffer->GetRHIImpl<IndexBuffer>()->Handle(), 0, VK_INDEX_TYPE_UINT32);
	}
	
	void CmdList::CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandBuffer->PushConstants(m_PipelineLayout, data, size, offset);
	}
	
	void CmdList::CmdFillBuffer(const SP<RHI::Buffer>& buffer, uint64_t dstOffset, uint64_t size, uint32_t data) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandBuffer->FillBuffer(buffer->GetRHIImpl<Buffer>()->Handle(), dstOffset, size, data);
	}

	void CmdList::CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->Draw(vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void CmdList::CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandBuffer->DrawIndexed(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
	}
	
	void CmdList::CmdDrawIndexedIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandBuffer->DrawIndexedIndirect(buffer->GetRHIImpl<Buffer>()->Handle(), offset, drawCount, stride);
	}

	void CmdList::CmdDrawIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandBuffer->DrawIndirect(buffer->GetRHIImpl<Buffer>()->Handle(), offset, drawCount, stride);
	}
	
	void CmdList::CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandBuffer->Dispatch(groupCountX, groupCountY, groupCountZ);
	}
	
	void CmdList::CmdDispatchIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Indirect->CmdDispatchIndirect(m_CommandBuffer, buffer->GetRHIImpl<Buffer>(), offset);
	}
	
	void CmdList::CmdInsertBarrier(const SP<RHI::RenderTarget>& renderTarget, const Graphic::ImageBarrierDesc& desc) const
	{
		NEPTUNE_PROFILE_ZONE
		
		CmdInsertBarrier(renderTarget->GetRHIImpl<RenderTarget>()->Handle(), desc);
	}
	
	void CmdList::CmdInsertBarrier(const Graphic::MemoryBarrierDesc& desc) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkMemoryBarrier2                  barrier{};
		barrier.sType                   = VK_STRUCTURE_TYPE_MEMORY_BARRIER_2;
		barrier.srcAccessMask           = ToVkAccessFlags(desc.srcAccess);
		barrier.dstAccessMask           = ToVkAccessFlags(desc.dstAccess);
		barrier.srcStageMask            = ToVkPipelineStageFlags(desc.srcStage);
		barrier.dstStageMask            = ToVkPipelineStageFlags(desc.dstStage);
		
		m_Synchronization->InsertBarrier(m_CommandBuffer.get(), barrier);
	}
	
	void CmdList::CmdSetViewport(const glm::uvec2& viewPortSize) const
	{
		NEPTUNE_PROFILE_ZONE

		VkViewport                     viewport{};
		viewport.x                  =  0.0f;
		viewport.y                  =  static_cast<float>(viewPortSize.y);
		viewport.width              =  static_cast<float>(viewPortSize.x);
		viewport.height             = -static_cast<float>(viewPortSize.y);
		viewport.minDepth           =  0.0f;
		viewport.maxDepth           =  1.0f;

		VkExtent2D                    extent;
		extent.width                = viewPortSize.x;
		extent.height               = viewPortSize.y;

		VkRect2D                      scissor{};
		scissor.offset              = { 0, 0 };
		scissor.extent              = extent;
			
		m_CommandBuffer->SetViewport(viewport);

		m_CommandBuffer->SetScissor(scissor);
	}

	void CmdList::SetRenderPass(const SP<RHI::RenderPass>& renderPass)
	{
		NEPTUNE_PROFILE_ZONE

		m_RenderPass = renderPass->GetRHIImpl<RenderPass>();
	}

	void CmdList::SetQueryPool(const SP<Resource::QueryPool>& queryPool)
	{
		NEPTUNE_PROFILE_ZONE

		m_QueryPool = queryPool.get();
	}

	void CmdList::CmdCopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->CopyImage(src, dst, region);
	}
	
	void CmdList::CmdCopyBuffer(VkBuffer src, VkBuffer dst, const VkBufferCopy& region) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->CopyBuffer(src, dst, region);
	}
	
	void CmdList::CopyBufferToImage(VkBuffer src, VkImage dst, VkImageLayout dstImageLayout, const VkBufferImageCopy& region) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->CopyBufferToImage(src, dst, dstImageLayout, region);
	}

	void CmdList::CmdInsertBarrier(VkImage image, const Graphic::ImageBarrierDesc& desc) const
	{
		NEPTUNE_PROFILE_ZONE
		
		VkImageMemoryBarrier2                       barrier{};
		barrier.sType                             = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
		barrier.srcAccessMask                     = ToVkAccessFlags(desc.memoryDesc.srcAccess);
		barrier.dstAccessMask                     = ToVkAccessFlags(desc.memoryDesc.dstAccess);
		barrier.srcStageMask                      = ToVkPipelineStageFlags(desc.memoryDesc.srcStage);
		barrier.dstStageMask                      = ToVkPipelineStageFlags(desc.memoryDesc.dstStage);
		barrier.oldLayout                         = m_ImageLayout->From(ToVkImageLayout(desc.srcLayout));
		barrier.newLayout                         = m_ImageLayout->From(ToVkImageLayout(desc.dstLayout));
		barrier.srcQueueFamilyIndex               = GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT);
		barrier.dstQueueFamilyIndex               = GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT);
		barrier.image                             = image;
		barrier.subresourceRange.aspectMask       = ToVkImageAspectFlags(desc.aspect);
		barrier.subresourceRange.baseMipLevel     = desc.baseMipLevel;
		barrier.subresourceRange.levelCount       = desc.levelCount;
		barrier.subresourceRange.baseArrayLayer   = desc.baseArrayLayer;
		barrier.subresourceRange.layerCount       = desc.layerCount;

		m_Synchronization->InsertBarrier(m_CommandBuffer.get(), barrier);
	}

	void CmdList::CmdBeginQuery(uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->BeginQuery(m_QueryPool->Handle(), index, m_QueryPool->Flag());
	}

	void CmdList::CmdEndQuery(uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->EndQuery(m_QueryPool->Handle(), index);
	}

	void CmdList::CmdWriteTimeStamp(uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->WriteTimeStamp(m_QueryPool->Handle(), index);
	}

	void CmdList::CmdResetQueryPool() const
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandBuffer->ResetQueryPool(m_QueryPool->Handle(), m_QueryPool->Count());
	}
}

#endif