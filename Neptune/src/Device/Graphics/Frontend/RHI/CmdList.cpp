/**
* @file CmdList.h.
* @brief The CmdList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "CmdList.h"

namespace Neptune::RHI {
	
	void RHI<ERHI::CmdList>::Impl::Translate(const CmdStream& stream)
	{
		NEPTUNE_PROFILE_ZONE
		
		std::vector<Graphic::ImageBarrierDesc>  imageBarrierBatch;
		std::vector<Graphic::MemoryBarrierDesc> memoryBarrierBatch;
		
		const auto flushBarriers = [&]() {
			
			if (imageBarrierBatch.empty() && memoryBarrierBatch.empty()) return;
			
			CmdInsertBarrier(memoryBarrierBatch, imageBarrierBatch);
			
			imageBarrierBatch.clear();
			memoryBarrierBatch.clear();
		};
		
		for (const auto& cmd : stream.Commands())
		{
			if (cmd.m_Op != ECmd::InsertImageBarrier && cmd.m_Op != ECmd::InsertMemoryBarrier)
			{
				flushBarriers();
			}
			
			switch (cmd.m_Op)
			{
				case ECmd::SetGraphicCmdList:
				{
					SetGraphicCmdList(cmd.m_Clock);
					break;
				}
				case ECmd::SetComputeCmdList:
				{
					SetComputeCmdList(cmd.m_Clock);
					break;
				}
				case ECmd::SetRenderPass:
				{
					SetRenderPass(stream.Ref<RenderPass>(cmd.m_Ref.ref));
					break;
				}
				case ECmd::BeginRenderPass:
				{
					CmdBeginRenderPass();
					break;
				}
				case ECmd::EndRenderPass:
				{
					CmdEndRenderPass();
					break;
				}
				case ECmd::BindDescriptor:
				{
					CmdBindDescriptor(stream.Ref<DescriptorList>(cmd.m_Ref.ref));
					break;
				}
				case ECmd::BindPipeline:
				{
					CmdBindPipeline(stream.Ref<Pipeline>(cmd.m_Ref.ref));
					break;
				}
				case ECmd::BindIndexBuffer:
				{
					CmdBindIndexBuffer(stream.Ref<IndexBuffer>(cmd.m_Ref.ref));
					break;
				}
				case ECmd::UpdateShaderConstant:
				{
					CmdUpdateShaderConstant(stream.BlobAt(cmd.m_Constant.blobOffset), cmd.m_Constant.blobSize, cmd.m_Constant.shaderOffset);
					break;
				}
				case ECmd::FillBuffer:
				{
					CmdFillBuffer(stream.Ref<Buffer>(cmd.m_Fill.ref), cmd.m_Fill.dstOffset, cmd.m_Fill.size, cmd.m_Fill.data);
					break;
				}
				case ECmd::Draw:
				{
					CmdDraw(cmd.m_Draw.vertexCount, cmd.m_Draw.instanceCount, cmd.m_Draw.firstVertex, cmd.m_Draw.firstInstance);
					break;
				}
				case ECmd::DrawIndexed:
				{
					CmdDrawIndexed(cmd.m_DrawIndexed.indexCount, cmd.m_DrawIndexed.instanceCount, cmd.m_DrawIndexed.firstIndex, cmd.m_DrawIndexed.vertexOffset, cmd.m_DrawIndexed.firstInstance);
					break;
				}
				case ECmd::DrawIndexedIndirect:
				{
					CmdDrawIndexedIndirect(stream.Ref<Buffer>(cmd.m_Indirect.ref), cmd.m_Indirect.offset, cmd.m_Indirect.drawCount, cmd.m_Indirect.stride);
					break;
				}
				case ECmd::DrawIndirect:
				{
					CmdDrawIndirect(stream.Ref<Buffer>(cmd.m_Indirect.ref), cmd.m_Indirect.offset, cmd.m_Indirect.drawCount, cmd.m_Indirect.stride);
					break;
				}
				case ECmd::Dispatch:
				{
					CmdDispatch(cmd.m_Dispatch.x, cmd.m_Dispatch.y, cmd.m_Dispatch.z);
					break;
				}
				case ECmd::DispatchIndirect:
				{
					CmdDispatchIndirect(stream.Ref<Buffer>(cmd.m_DispatchIndirect.ref), cmd.m_DispatchIndirect.offset);
					break;
				}
				case ECmd::InsertImageBarrier:
				{
					imageBarrierBatch.emplace_back(stream.ImageBarrier(cmd.m_Barrier.desc));
					break;
				}
				case ECmd::InsertMemoryBarrier:
				{
					memoryBarrierBatch.emplace_back(stream.MemoryBarrier(cmd.m_Barrier.desc));
					break;
				}
				case ECmd::SetViewport:
				{
					CmdSetViewport(glm::uvec2(cmd.m_Viewport.width, cmd.m_Viewport.height));
					break;
				}
				case ECmd::ExecuteNative:
				{
					std::invoke(stream.Native(cmd.m_Native.native), GetCommandList());
					break;
				}
				default:
				{
					NEPTUNE_LOG_CORE(E) << "Invalid ECmd in CmdList::Translate.";
					
					NEPTUNE_ASSERT(false)
					
					break;
				}
			}
		}
		
		flushBarriers();
	}

	void CmdList::SetGraphicCmdList(const Data::Clock& clock)
	{
		m_Stream.Push(ECmd::SetGraphicCmdList).m_Clock = clock;
	}

	void CmdList::SetComputeCmdList(const Data::Clock& clock)
	{
		m_Stream.Push(ECmd::SetComputeCmdList).m_Clock = clock;
	}

	void* CmdList::GetCommandList() const
	{
		return RHICmdList::m_Impl->GetCommandList();
	}

	void CmdList::SetRenderPass(const SP<RenderPass>& renderPass)
	{
		m_Stream.Push(ECmd::SetRenderPass).m_Ref = { m_Stream.Keep(renderPass) };
	}

	void CmdList::CmdBeginRenderPass()
	{
		m_Stream.Push(ECmd::BeginRenderPass);
	}

	void CmdList::CmdEndRenderPass()
	{
		m_Stream.Push(ECmd::EndRenderPass);
	}

	void CmdList::CmdBindDescriptor(const SP<DescriptorList>& descriptorList)
	{
		m_Stream.Push(ECmd::BindDescriptor).m_Ref = { m_Stream.Keep(descriptorList) };
	}

	void CmdList::CmdBindPipeline(const SP<Pipeline>& pipeline)
	{
		m_Stream.Push(ECmd::BindPipeline).m_Ref = { m_Stream.Keep(pipeline) };
	}

	void CmdList::CmdBindIndexBuffer(const SP<IndexBuffer>& buffer)
	{
		m_Stream.Push(ECmd::BindIndexBuffer).m_Ref = { m_Stream.Keep(buffer) }; 
	}

	void CmdList::CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset)
	{
		const auto blob = m_Stream.PushBlob(data, size);
			
		m_Stream.Push(ECmd::UpdateShaderConstant).m_Constant = { blob, size, offset };
	}

	void CmdList::CmdFillBuffer(const SP<Buffer>& buffer, uint64_t dstOffset, uint64_t size, uint32_t data)
	{
		const auto ref = m_Stream.Keep(buffer);
			
		m_Stream.Push(ECmd::FillBuffer).m_Fill = { ref, dstOffset, size, data };
	}

	void CmdList::CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
	{
		m_Stream.Push(ECmd::Draw).m_Draw = { vertexCount, instanceCount, firstVertex, firstInstance };
	}

	void CmdList::CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
	{
		m_Stream.Push(ECmd::DrawIndexed).m_DrawIndexed = { indexCount, instanceCount, firstIndex, vertexOffset, firstInstance };
	}

	void CmdList::CmdDrawIndexedIndirect(const SP<Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride)
	{
		const auto ref = m_Stream.Keep(buffer);
			
		m_Stream.Push(ECmd::DrawIndexedIndirect).m_Indirect = { ref, offset, drawCount, stride };
	}

	void CmdList::CmdDrawIndirect(const SP<Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride)
	{
		const auto ref = m_Stream.Keep(buffer);
			
		m_Stream.Push(ECmd::DrawIndirect).m_Indirect = { ref, offset, drawCount, stride };
	}

	void CmdList::CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
	{
		m_Stream.Push(ECmd::Dispatch).m_Dispatch = { groupCountX, groupCountY, groupCountZ };
	}

	void CmdList::CmdDispatchIndirect(const SP<Buffer>& buffer, uint64_t offset)
	{
		const auto ref = m_Stream.Keep(buffer);
			
		m_Stream.Push(ECmd::DispatchIndirect).m_DispatchIndirect = { ref, offset };
	}

	void CmdList::CmdInsertBarrier(const Graphic::ImageBarrierDesc& desc)
	{
		m_Stream.Push(ECmd::InsertImageBarrier).m_Barrier = { m_Stream.PushImageBarrier(desc) };
	}

	void CmdList::CmdInsertBarrier(const Graphic::MemoryBarrierDesc& desc)
	{
		m_Stream.Push(ECmd::InsertMemoryBarrier).m_Barrier = { m_Stream.PushMemoryBarrier(desc) };
	}

	void CmdList::CmdInsertBarrier(const std::vector<Graphic::MemoryBarrierDesc>& memoryBatch, const std::vector<Graphic::ImageBarrierDesc>& imageBatch)
	{
		for (const auto& desc : memoryBatch)
		{
			m_Stream.Push(ECmd::InsertMemoryBarrier).m_Barrier = { m_Stream.PushMemoryBarrier(desc) };
		}
		
		for (const auto& desc : imageBatch)
		{
			m_Stream.Push(ECmd::InsertImageBarrier).m_Barrier = { m_Stream.PushImageBarrier(desc) };
		}
	}
	
	void CmdList::CmdSetViewport(const glm::uvec2& viewPortSize)
	{
		m_Stream.Push(ECmd::SetViewport).m_Viewport = { viewPortSize.x, viewPortSize.y };
	}

	void CmdList::CmdExecuteNative(std::function<void(void*)> fn)
	{
		m_Stream.Push(ECmd::ExecuteNative).m_Native = { m_Stream.PushNative(std::move(fn)) };
	}
}
