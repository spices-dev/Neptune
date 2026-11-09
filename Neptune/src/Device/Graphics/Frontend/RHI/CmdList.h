/**
* @file CmdList.h.
* @brief The CmdList Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Device/Graphics/Frontend/Memory.h"

#include <glm/vec2.hpp>

namespace Neptune::Graphic {

	struct MemoryBarrierDesc;
}

namespace Neptune::Data {

	struct Clock;
}

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
	class IndexBuffer;
	class Buffer;
	class RenderTarget;
	
	using RHICmdList = RHI<ERHI::CmdList>;

	/**
	* @brief Specialization of RHICmdList::Impl
	*/
	template<>
	class RHICmdList::Impl : public RHIImplEmpty
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Impl() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Impl() = default;

		/***********************************************************************************/

		/********************************** Context ****************************************/

		/**
		* @brief Interface of Set Graphic CommandList Context.
		* 
		* @param[in] clock Clock.
		*/
		virtual void SetGraphicCmdList(const Data::Clock& clock) = 0;

		/**
		* @brief Interface of Set Compute CommandList Context.
		* 
		* @param[in] clock Clock.
		*/
		virtual void SetComputeCmdList(const Data::Clock& clock) = 0;
		
		/**
		* @brief Interface of Get Current CommandList.
		* 
		* @return Returns Current CommandList.
		*/
		virtual void* GetCommandList() const = 0;
		
		/***********************************************************************************/

		/********************************* Reference ***************************************/

		/**
		* @brief Interface of Set RenderPass Reference.
		*
		* @param[in] renderPass RenderPass.
		*/
		virtual void SetRenderPass(const SP<RenderPass>& renderPass) = 0;

		/***********************************************************************************/

		/********************************* Commands ****************************************/

		/**
		* @brief Interface of BeginRenderPass.
		*/
		virtual void CmdBeginRenderPass() const = 0;

		/**
		* @brief Interface of EndRenderPass.
		*/
		virtual void CmdEndRenderPass() const = 0;

		/**
		* @brief Interface of BindDescriptor.
		* 
		* @param[in] descriptorList DescriptorList.
		*/
		virtual void CmdBindDescriptor(const SP<DescriptorList>& descriptorList) const = 0;

		/**
		* @brief Interface of BindPipeline.
		* 
		* @param[in] pipeline Pipeline.
		*/
		virtual void CmdBindPipeline(const SP<Pipeline>& pipeline) = 0;

		/**
		* @brief Bind IndexBuffer.
		*
		* @param[in] buffer IndexBuffer.
		*/
		virtual void CmdBindIndexBuffer(const SP<IndexBuffer>& buffer) const = 0;
		
		/**
		* @brief Interface of Update ShaderConstant.
		*
		* @param[in] data ShaderConstant data.
		* @param[in] size ShaderConstant size.
		* @param[in] offset ShaderConstant offset.
		*/
		virtual void CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset = 0) const = 0;
		
		/**
		* @brief Interface of FillBuffer.
		*
		* @param[in] buffer Buffer.
		* @param[in] dstOffset offset.
		* @param[in] size size.
		* @param[in] data data.
		*/
		virtual void CmdFillBuffer(const SP<Buffer>& buffer, uint64_t dstOffset, uint64_t size, uint32_t data) const = 0;
		
		/**
		* @brief Interface of Draw.
		* 
		* @param[in] vertexCount .
		* @param[in] instanceCount .
		* @param[in] firstVertex .
		* @param[in] firstInstance .
		*/
		virtual void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const = 0;

		/**
		* @brief Interface of DrawIndexed.
		* 
		* @param[in] indexCount .
		* @param[in] instanceCount .
		* @param[in] firstIndex .
		* @param[in] vertexOffset .
		* @param[in] firstInstance .
		*/
		virtual void CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const = 0;

		/**
		* @brief Interface of DrawIndexedIndirect.
		*
		* @param[in] buffer Buffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		virtual void CmdDrawIndexedIndirect(const SP<Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const = 0;
		
		/**
		* @brief Interface of DrawIndirect.
		*
		* @param[in] buffer Buffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		virtual void CmdDrawIndirect(const SP<Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const = 0;
		
		/**
		* @brief Interface of Dispatch.
		* 
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		virtual void CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const = 0;
		
		/**
		* @brief Interface of CmdDispatchIndirect.
		* 
		* @param[in] buffer  Buffer.
		* @param[in] offset .
		*/
		virtual void CmdDispatchIndirect(const SP<Buffer>& buffer, uint64_t offset) const = 0;
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] renderTarget RenderTarget.
		* @param[in] desc MemoryBarrierDesc.
		*/
		virtual void CmdInsertBarrier(const SP<RenderTarget>& renderTarget, const Graphic::ImageBarrierDesc& desc) const = 0;
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] desc MemoryBarrierDesc.
		*/
		virtual void CmdInsertBarrier(const Graphic::MemoryBarrierDesc& desc) const = 0;
		
		/**
		* @brief Interface of SetViewport.
		* 
		* @param[in] viewPortSize .
		*/
		virtual void CmdSetViewport(const glm::uvec2& viewPortSize) const = 0;

		/***********************************************************************************/
	};

	/**
	* @brief RHI of ERHI::CmdList
	*/
	class CmdList : public RHICmdList
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		CmdList() = default;

		/**
		* @brief Destructor Function.
		*/
		~CmdList() override = default;

		/**
		* @brief Interface of Set Graphic CommandList Context.
		*
		* @param[in] clock Clock.
		*/
		void SetGraphicCmdList(const Data::Clock& clock) const { RHICmdList::m_Impl->SetGraphicCmdList(clock); }

		/**
		* @brief Interface of Set Graphic Compute Context.
		*
		* @param[in] clock Clock.
		*/
		void SetComputeCmdList(const Data::Clock& clock) const { RHICmdList::m_Impl->SetComputeCmdList(clock); }
		
		/**
		* @brief Interface of Get Current CommandList.
		* 
		* @return Returns Current CommandList.
		*/
		void* GetCommandList() const { return RHICmdList::m_Impl->GetCommandList(); }
		
		/**
		* @brief Interface of Set RenderPass Reference.
		*
		* @param[in] renderPass RenderPass.
		*/
		void SetRenderPass(const SP<RenderPass>& renderPass) const { RHICmdList::m_Impl->SetRenderPass(renderPass); }

		/**
		* @brief Interface of BeginRenderPass.
		*/
		void CmdBeginRenderPass() const { RHICmdList::m_Impl->CmdBeginRenderPass(); }

		/**
		* @brief Interface of EndRenderPass.
		*/
		void CmdEndRenderPass() const { RHICmdList::m_Impl->CmdEndRenderPass(); }

		/**
		* @brief Interface of BindDescriptor.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		void CmdBindDescriptor(const SP<DescriptorList>& descriptorList) const { RHICmdList::m_Impl->CmdBindDescriptor(descriptorList); }

		/**
		* @brief Interface of BindPipeline.
		*
		* @param[in] pipeline Pipeline.
		*/
		void CmdBindPipeline(const SP<Pipeline>& pipeline) const { RHICmdList::m_Impl->CmdBindPipeline(pipeline); }

		/**
		* @brief Bind IndexBuffer.
		*
		* @param[in] buffer IndexBuffer.
		*/
		void CmdBindIndexBuffer(const SP<IndexBuffer>& buffer) const { RHICmdList::m_Impl->CmdBindIndexBuffer(buffer); }

		/**
		* @brief Interface of Update ShaderConstant.
		*
		* @param[in] data ShaderConstant data.
		* @param[in] size ShaderConstant size.
		* @param[in] offset ShaderConstant offset.
		*/
		void CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset = 0) const { RHICmdList::m_Impl->CmdUpdateShaderConstant(data, size, offset); }
		
		/**
		* @brief Interface of FillBuffer.
		*
		* @param[in] buffer Buffer.
		* @param[in] dstOffset offset.
		* @param[in] size size.
		* @param[in] data data.
		*/
		void CmdFillBuffer(const SP<Buffer>& buffer, uint64_t dstOffset, uint64_t size, uint32_t data) const { RHICmdList::m_Impl->CmdFillBuffer(buffer, dstOffset, size, data); }
		
		/**
		* @brief Interface of Draw.
		* 
		* @param[in] vertexCount .
		* @param[in] instanceCount .
		* @param[in] firstVertex .
		* @param[in] firstInstance .
		*/
		void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const { RHICmdList::m_Impl->CmdDraw(vertexCount, instanceCount, firstVertex, firstInstance); }

		/**
		* @brief Interface of DrawIndexed.
		* 
		* @param[in] indexCount .
		* @param[in] instanceCount .
		* @param[in] firstIndex .
		* @param[in] vertexOffset .
		* @param[in] firstInstance .
		*/
		void CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const { RHICmdList::m_Impl->CmdDrawIndexed(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance); }

		/**
		* @brief Interface of DrawIndexedIndirect.
		*
		* @param[in] buffer Buffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void CmdDrawIndexedIndirect(const SP<Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const { RHICmdList::m_Impl->CmdDrawIndexedIndirect(buffer, offset, drawCount, stride); }
		
		/**
		* @brief Interface of DrawIndirect.
		*
		* @param[in] buffer Buffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void CmdDrawIndirect(const SP<Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const { RHICmdList::m_Impl->CmdDrawIndirect(buffer, offset, drawCount, stride); }
		
		/**
		* @brief Interface of Dispatch.
		* 
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		void CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const { RHICmdList::m_Impl->CmdDispatch(groupCountX, groupCountY, groupCountZ); }
		
		/**
		* @brief Interface of CmdDispatchIndirect.
		* 
		* @param[in] buffer  Buffer.
		* @param[in] offset .
		*/
		void CmdDispatchIndirect(const SP<Buffer>& buffer, uint64_t offset) const { RHICmdList::m_Impl->CmdDispatchIndirect(buffer, offset); }
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] renderTarget RenderTarget.
		* @param[in] desc MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const SP<RenderTarget>& renderTarget, const Graphic::ImageBarrierDesc& desc) const { RHICmdList::m_Impl->CmdInsertBarrier(renderTarget, desc); }
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] desc MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const Graphic::MemoryBarrierDesc& desc) const { RHICmdList::m_Impl->CmdInsertBarrier(desc); }
		
		/**
		* @brief Interface of SetViewport.
		*
		* @param[in] viewPortSize .
		*/
		void CmdSetViewport(const glm::uvec2& viewPortSize) const { RHICmdList::m_Impl->CmdSetViewport(viewPortSize); }
	};
}