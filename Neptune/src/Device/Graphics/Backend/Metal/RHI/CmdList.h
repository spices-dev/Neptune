/**
* @file CmdList.h.
* @brief The CmdList Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Device/Graphics/Backend/Metal/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Frontend/RHI/CmdList.h"

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
	class IndexBuffer;
}

namespace Neptune::Metal {

	class RenderPass;
	class VideoSession;
	class Image;
	class QueryPool;

	/**
	* @brief Metal::CmdList Class.
	* This class defines the Metal::CmdList behaves.
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
		* @brief Interface of Draw.
		* 
		* @param[in] vertexCount .
		* @param[in] instanceCount .
		* @param[in] firstVertex .
		* @param[in] firstInstance .
		*/
		void CmdDraw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const override;

		/**
		* @brief Interface of DrawInstance.
		* 
		* @param[in] indexCount .
		* @param[in] instanceCount .
		* @param[in] firstIndex .
		* @param[in] vertexOffset .
		* @param[in] firstInstance .
		*/
		void CmdDrawInstance(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const override;

		/**
		* @brief Interface of Dispatch.
		* 
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		void CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const override;
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] barrier MemoryBarrier.
		*/
		void CmdInsertBarrier(const MemoryBarrier& barrier) const override;
		
		/**
		* @brief Interface of SetViewport.
		*
		* @param[in] viewPortSize .
		*/
		void CmdSetViewport(const glm::vec2& viewPortSize) const override;

	protected:

		uint32_t                      m_FrameIndex     = 0;                                     // @brief Frame index.
		uint32_t                      m_ImageIndex     = 0;                                     // @brief Image index.

		const RenderPass*             m_RenderPass     = nullptr;                               // @brief RenderPass reference.
		const QueryPool*              m_QueryPool      = nullptr;                               // @brief QueryPool reference.
	};
}

#endif