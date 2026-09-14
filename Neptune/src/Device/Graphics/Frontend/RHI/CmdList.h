/**
* @file CmdList.h.
* @brief The CmdList Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Device/Graphics/Frontend/Memory.h"

#include <glm/ext/vector_float2.hpp>

namespace Neptune::Graphic {

	struct MemoryBarrierDesc;
}

namespace Neptune::Data {

	struct Clock;
}

namespace Neptune::RHI {

	using RHICmdList = RHI<ERHI::CmdList>;

	/**
	* @brief Specialization of RHICmdList::Impl
	*/
	template<>
	class RHICmdList::Impl
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
		virtual void SetRenderPass(const SP<class RenderPass>& renderPass) = 0;

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
		virtual void CmdBindDescriptor(const SP<class DescriptorList>& descriptorList) const = 0;

		/**
		* @brief Interface of BindPipeline.
		* 
		* @param[in] pipeline Pipeline.
		*/
		virtual void CmdBindPipeline(const SP<class Pipeline>& pipeline) = 0;

		/**
		* @brief Bind IndexBuffer.
		*
		* @param[in] buffer IndexBuffer.
		*/
		virtual void CmdBindIndexBuffer(const SP<class IndexBuffer>& buffer) const = 0;
		
		/**
		* @brief Interface of Update ShaderConstant.
		*
		* @param[in] data ShaderConstant data.
		* @param[in] size ShaderConstant size.
		* @param[in] offset ShaderConstant offset.
		*/
		virtual void CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset = 0) const = 0;
		
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
		* @brief Interface of Dispatch.
		* 
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		virtual void CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const = 0;
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] barrier MemoryBarrierDesc.
		*/
		virtual void CmdInsertBarrier(const Graphic::MemoryBarrierDesc& barrier) const = 0;
		
		/**
		* @brief Interface of SetViewport.
		* 
		* @param[in] viewPortSize .
		*/
		virtual void CmdSetViewport(const glm::vec2& viewPortSize) const = 0;

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
		void SetRenderPass(const SP<class RenderPass>& renderPass) const { RHICmdList::m_Impl->SetRenderPass(renderPass); }

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
		void CmdBindDescriptor(const SP<class DescriptorList>& descriptorList) const { RHICmdList::m_Impl->CmdBindDescriptor(descriptorList); }

		/**
		* @brief Interface of BindPipeline.
		*
		* @param[in] pipeline Pipeline.
		*/
		void CmdBindPipeline(const SP<class Pipeline>& pipeline) const { RHICmdList::m_Impl->CmdBindPipeline(pipeline); }

		/**
		* @brief Bind IndexBuffer.
		*
		* @param[in] buffer IndexBuffer.
		*/
		void CmdBindIndexBuffer(const SP<class IndexBuffer>& buffer) const { RHICmdList::m_Impl->CmdBindIndexBuffer(buffer); }

		/**
		* @brief Interface of Update ShaderConstant.
		*
		* @param[in] data ShaderConstant data.
		* @param[in] size ShaderConstant size.
		* @param[in] offset ShaderConstant offset.
		*/
		void CmdUpdateShaderConstant(const void* data, uint32_t size, uint32_t offset = 0) const { RHICmdList::m_Impl->CmdUpdateShaderConstant(data, size, offset); }
		
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
		* @brief Interface of Dispatch.
		* 
		* @param[in] groupCountX .
		* @param[in] groupCountY .
		* @param[in] groupCountZ .
		*/
		void CmdDispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const { RHICmdList::m_Impl->CmdDispatch(groupCountX, groupCountY, groupCountZ); }
		
		/**
		* @brief Interface of Insert Barrier.
		* 
		* @param[in] barrier MemoryBarrierDesc.
		*/
		void CmdInsertBarrier(const Graphic::MemoryBarrierDesc& barrier) const { RHICmdList::m_Impl->CmdInsertBarrier(barrier); }
		
		/**
		* @brief Interface of SetViewport.
		*
		* @param[in] viewPortSize .
		*/
		void CmdSetViewport(const glm::vec2& viewPortSize) const { RHICmdList::m_Impl->CmdSetViewport(viewPortSize); }
	};
}