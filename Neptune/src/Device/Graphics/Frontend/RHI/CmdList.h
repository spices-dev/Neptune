/**
* @file CmdList.h.
* @brief The CmdList Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "CmdStream.h"
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
		~Impl() override = default;

		/**
		* @brief Translate CmdStream.
		* 
		* @param[in] stream CmdStream.
		*/
		void Translate(const CmdStream& stream);
		
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
		* @param[in] desc MemoryBarrierDesc.
		*/
		virtual void CmdInsertBarrier(const Graphic::ImageBarrierDesc& desc) const = 0;
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] desc MemoryBarrierDesc.
		*/
		virtual void CmdInsertBarrier(const Graphic::MemoryBarrierDesc& desc) const = 0;
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] memoryBatch MemoryBarrierDesc.
		* @param[in] imageBatch MemoryBarrierDesc.
		*/
		virtual void CmdInsertBarrier(const std::vector<Graphic::MemoryBarrierDesc>& memoryBatch, const std::vector<Graphic::ImageBarrierDesc>& imageBatch) const = 0;
		
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
		* @brief Reset CmdStream.
		*/
		void Reset() { m_Stream.Reset(); }
		
		/**
		* @brief Translate CmdStream.
		*/
		void Translate() const { RHICmdList::m_Impl->Translate(m_Stream); }
		
		/**
		* @brief Interface of Set Graphic CommandList Context.
		*
		* @param[in] clock Clock.
		*/
		void SetGraphicCmdList(const Data::Clock& clock);

		/**
		* @brief Interface of Set Graphic Compute Context.
		*
		* @param[in] clock Clock.
		*/
		void SetComputeCmdList(const Data::Clock& clock);
		
		/**
		* @brief Interface of Get Current CommandList.
		* 
		* @return Returns Current CommandList.
		*/
		void* GetCommandList() const;
		
		/**
		* @brief Interface of Set RenderPass Reference.
		*
		* @param[in] renderPass RenderPass.
		*/
		void SetRenderPass(const SP<RenderPass>& renderPass);

		/**
		* @brief Interface of BeginRenderPass.
		*/
		void CmdBeginRenderPass();

		/**
		* @brief Interface of EndRenderPass.
		*/
		void CmdEndRenderPass();

		/**
		* @brief Interface of BindDescriptor.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		void CmdBindDescriptor(const SP<DescriptorList>& descriptorList);

		/**
		* @brief Interface of BindPipeline.
		*
		* @param[in] pipeline Pipeline.
		*/
		void CmdBindPipeline(const SP<Pipeline>& pipeline);

		/**
		* @brief Bind IndexBuffer.
		*
		* @param[in] buffer IndexBuffer.
		*/
		void CmdBindIndexBuffer(const SP<IndexBuffer>& buffer);

		/**
		* @brief Interface of Update ShaderConstant.
		*
		* @param[in] data ShaderConstant data.
		* @param[in] size ShaderConstant size.
		* @param[in] offset ShaderConstant offset.
		*/
		void CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset = 0);
		
		/**
		* @brief Interface of FillBuffer.
		*
		* @param[in] buffer Buffer.
		* @param[in] dstOffset offset.
		* @param[in] size size.
		* @param[in] data data.
		*/
		void CmdFillBuffer(const SP<Buffer>& buffer, uint64_t dstOffset, uint64_t size, uint32_t data);
		
		/**
		* @brief Interface of Draw.
		* 
		* @param[in] vertexCount .
		* @param[in] instanceCount .
		* @param[in] firstVertex .
		* @param[in] firstInstance .
		*/
		void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);

		/**
		* @brief Interface of DrawIndexed.
		* 
		* @param[in] indexCount .
		* @param[in] instanceCount .
		* @param[in] firstIndex .
		* @param[in] vertexOffset .
		* @param[in] firstInstance .
		*/
		void CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);

		/**
		* @brief Interface of DrawIndexedIndirect.
		*
		* @param[in] buffer Buffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void CmdDrawIndexedIndirect(const SP<Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride);
		
		/**
		* @brief Interface of DrawIndirect.
		*
		* @param[in] buffer Buffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void CmdDrawIndirect(const SP<Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride);
		
		/**
		* @brief Interface of Dispatch.
		* 
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		void CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
		
		/**
		* @brief Interface of CmdDispatchIndirect.
		* 
		* @param[in] buffer  Buffer.
		* @param[in] offset .
		*/
		void CmdDispatchIndirect(const SP<Buffer>& buffer, uint64_t offset);
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] desc MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const Graphic::ImageBarrierDesc& desc);
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] desc MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const Graphic::MemoryBarrierDesc& desc);
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] memoryBatch MemoryBarrierDesc.
		* @param[in] imageBatch MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const std::vector<Graphic::MemoryBarrierDesc>& memoryBatch, const std::vector<Graphic::ImageBarrierDesc>& imageBatch);
		
		/**
		* @brief Interface of SetViewport.
		*
		* @param[in] viewPortSize .
		*/
		void CmdSetViewport(const glm::uvec2& viewPortSize);
		
		/**
		* @brief Interface of Execute Native Function.
		*
		* @param[in] fn Native Function.
		*/
		void CmdExecuteNative(std::function<void(void*)> fn);
		
	private:
		
		CmdStream m_Stream;  // @brief CmdStream.
	};
}