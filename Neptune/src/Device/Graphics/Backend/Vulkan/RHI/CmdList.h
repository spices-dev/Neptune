/**
* @file CmdList.h.
* @brief The CmdList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/ISynchronization.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/IIndirect.h"

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
	class IndexBuffer;
	class Buffer;
	class RenderTarget;
}

namespace Neptune::Vulkan {

	namespace Resource {

		class VideoSession;
		class Image;
		class QueryPool;
	}

	class RenderPass;
	
	/**
	* @brief Vulkan::CmdList Class.
	* This class defines the Vulkan::CmdList behaves.
	*/
	class CmdList : public ContextAccessor, public RHI::RHICmdList::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit CmdList(Context& context);

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
		void CmdInsertBarrier(const SP<RHI::RenderTarget>& renderTarget, const Graphic::ImageBarrierDesc& desc) const override;
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] desc MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const Graphic::MemoryBarrierDesc& desc) const override;
		
		/**
		* @brief Interface of SetViewport.
		*
		* @param[in] viewPortSize .
		*/
		void CmdSetViewport(const glm::uvec2& viewPortSize) const override;

	public:

		/**
		* @brief Set QueryPool.
		*
		* @param[in] queryPool QueryPool.
		*/
		void SetQueryPool(const SP<Resource::QueryPool>& queryPool);

		/**
		* @brief Copy Image.
		*
		* @param[in] src VkImage.
		* @param[in] dst VkImage.
		* @param[in] region VkImageCopy.
		*/
		void CmdCopyImage(VkImage src, VkImage dst, const VkImageCopy& region) const;

		/**
		* @brief Copy Buffer.
		*
		* @param[in] src VkBuffer.
		* @param[in] dst VkBuffer.
		* @param[in] region VkBufferCopy.
		*/
		void CmdCopyBuffer(VkBuffer src, VkBuffer dst, const VkBufferCopy& region) const;

		/**
		* @brief Insert Barrier.
		* 
		* @param[in] image VkImage.
		* @param[in] desc MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(VkImage image, const Graphic::ImageBarrierDesc& desc) const;
		
		/**
		* @brief Begin Query.
		*
		* @param[in] index .
		*/
		void CmdBeginQuery(uint32_t index) const;

		/**
		* @brief End Query.
		*
		* @param[in] index .
		*/
		void CmdEndQuery(uint32_t index) const;

		/**
		* @brief Write TimeStamp.
		*
		* @param[in] index .
		*/
		void CmdWriteTimeStamp(uint32_t index) const;

		/**
		* @brief Reset QueryPool.
		*/
		void CmdResetQueryPool() const;

	protected:

		uint32_t                             m_FrameIndex     = 0;                                     // @brief Frame index.
		uint32_t                             m_ImageIndex     = 0;                                     // @brief Image index.

		SP<Unit::CommandBuffer>              m_CommandBuffer  = nullptr;                               // @brief CommandBuffer reference.
		const RenderPass*                    m_RenderPass     = nullptr;                               // @brief RenderPass reference.
		const Resource::QueryPool*           m_QueryPool      = nullptr;                               // @brief QueryPool reference.
		VkPipelineBindPoint                  m_BindPoint      = VK_PIPELINE_BIND_POINT_MAX_ENUM;       // @brief VkPipelineBindPoint.
		VkPipelineLayout                     m_PipelineLayout = VK_NULL_HANDLE;                        // @brief VkPipelineLayout.
		UP<Middleware::ISynchronization>     m_Synchronization;                                        // @brief ISynchronization.
		UP<Middleware::IIndirect>            m_Indirect;                                               // @brief IIndirect.
	};
}

#endif