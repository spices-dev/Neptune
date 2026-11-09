/**
* @file CmdList.h.
* @brief The CmdList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"

namespace Neptune::WebGPU::Unit {
	
	class CommandEncoder;
}

namespace Neptune::WebGPU {

	class RenderPass;
	class VideoSession;
	class Image;
	class QueryPool;

	/**
	* @brief WebGPU::CmdList Class.
	* This class defines the WebGPU::CmdList behaves.
	*/
	class CmdList : public ContextAccessor, public RHI::RHICmdList::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit CmdList(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~CmdList() override = default;

	public:

		/**
		* @brief Interface of Set Graphic CommandList Context.
		*
		* @param[in] clock Clock.
		*/
		void SetGraphicCmdList(const Data::Clock& clock) override;

		/**
		* @brief Interface of Set Compute CommandList Context.
		*
		* @param[in] clock Clock.
		*/
		void SetComputeCmdList(const Data::Clock& clock) override;
		
		/**
		* @brief Interface of Get Current CommandList.
		* 
		* @return Returns Current CommandList.
		*/
		void* GetCommandList() const override;
		
		/**
		* @brief Interface of Set RenderPass Reference.
		*
		* @param[in] renderPass RenderPass.
		*/
		void SetRenderPass(const SP<RHI::RenderPass>& renderPass) override;

		/**
		* @brief Interface of BeginRenderPass.
		*/
		void CmdBeginRenderPass() const override;

		/**
		* @brief Interface of EndRenderPass.
		*/
		void CmdEndRenderPass() const override;

		/**
		* @brief Interface of BindDescriptor.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		void CmdBindDescriptor(const SP<RHI::DescriptorList>& descriptorList) const override;

		/**
		* @brief Interface of BindPipeline.
		*
		* @param[in] pipeline Pipeline.
		*/
		void CmdBindPipeline(const SP<RHI::Pipeline>& pipeline) override;

		/**
		* @brief Bind IndexBuffer.
		*
		* @param[in] buffer IndexBuffer.
		*/
		void CmdBindIndexBuffer(const SP<RHI::IndexBuffer>& buffer) const override;
		
		/**
		* @brief Interface of Update ShaderConstant.
		*
		* @param[in] data ShaderConstant data.
		* @param[in] size ShaderConstant size.
		* @param[in] offset ShaderConstant offset.
		*/
		void CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset = 0) const override;
		
		/**
		* @brief Interface of FillBuffer.
		*
		* @param[in] buffer Buffer.
		* @param[in] dstOffset offset.
		* @param[in] size size.
		* @param[in] data data.
		*/
		void CmdFillBuffer(const SP<RHI::Buffer>& buffer, uint64_t dstOffset, uint64_t size, uint32_t data) const override;
		
		/**
		* @brief Interface of Draw.
		* 
		* @param[in] vertexCount .
		* @param[in] instanceCount .
		* @param[in] firstVertex .
		* @param[in] firstInstance .
		*/
		void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const override;

		/**
		* @brief Interface of DrawIndexed.
		* 
		* @param[in] indexCount .
		* @param[in] instanceCount .
		* @param[in] firstIndex .
		* @param[in] vertexOffset .
		* @param[in] firstInstance .
		*/
		void CmdDrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const override;

		/**
		* @brief Interface of DrawIndexedIndirect.
		*
		* @param[in] buffer Buffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void CmdDrawIndexedIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const override;
		
		/**
		* @brief Interface of DrawIndirect.
		*
		* @param[in] buffer Buffer.
		* @param[in] offset .
		* @param[in] drawCount .
		* @param[in] stride .
		*/
		void CmdDrawIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset, uint32_t drawCount, uint32_t stride) const override;
		
		/**
		* @brief Interface of Dispatch.
		* 
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		void CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const override;
		
		/**
		* @brief Interface of CmdDispatchIndirect.
		* 
		* @param[in] buffer  Buffer.
		* @param[in] offset .
		*/
		void CmdDispatchIndirect(const SP<RHI::Buffer>& buffer, uint64_t offset) const override;
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] renderTarget RenderTarget.
		* @param[in] desc MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const SP<RHI::RenderTarget>& renderTarget, const Graphic::ImageBarrierDesc& desc) const override {}
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] desc MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const Graphic::MemoryBarrierDesc& desc) const override {}
		
		/**
		* @brief Interface of SetViewport.
		*
		* @param[in] viewPortSize .
		*/
		void CmdSetViewport(const glm::uvec2& viewPortSize) const override;

	public:
		
		/**
		* @brief Copy Image To Image.
		* 
		* @param[in] source WGPUTexelCopyTextureInfo.
		* @param[in] destination WGPUTexelCopyTextureInfo.
		* @param[in] copySize WGPUExtent3D.
		*/
		void CmdCopyImage(const WGPUTexelCopyTextureInfo& source, const WGPUTexelCopyTextureInfo& destination, const WGPUExtent3D& copySize) const;
		
		/**
		* @brief Copy Buffer To Buffer.
		* 
		* @param[in] source WGPUBuffer.
		* @param[in] sourceOffset .
		* @param[in] destination WGPUBuffer.
		* @param[in] destinationOffset .
		* @param[in] size .
		*/
		void CmdCopyBuffer(WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) const;
		
	protected:

		SP<Unit::CommandEncoder>      m_CommandEncoder   = nullptr;         // @brief CommandEncoder reference.
		bool                          m_RenderBindPoint  = true;            // @brief Bind Point.
		RenderPass*                   m_RenderPass       = nullptr;         // @brief RenderPass reference.
		const QueryPool*              m_QueryPool        = nullptr;         // @brief QueryPool reference.
	};
}

#endif