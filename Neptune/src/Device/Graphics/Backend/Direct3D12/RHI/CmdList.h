/**
* @file CmdList.h.
* @brief The CmdList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"

namespace Neptune::Direct3D12::Resource {
	
	class CommandList;
}

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
	class IndexBuffer;
	class Buffer;
	class RenderTarget;;
}

namespace Neptune::Direct3D12 {

	class RenderPass;
	class VideoSession;
	class Image;
	class QueryPool;

	/**
	* @brief Direct3D12::CmdList Class.
	* This class defines the Direct3D12::CmdList behaves.
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
		
	protected:

		SP<Resource::CommandList>        m_CommandList    = nullptr;                               // @brief GraphicsCommandList reference.
		const RenderPass*                m_RenderPass     = nullptr;                               // @brief RenderPass reference.
		
	};
}

#endif