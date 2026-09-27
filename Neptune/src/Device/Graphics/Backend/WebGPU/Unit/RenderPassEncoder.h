/**
* @file RenderPassEncoder.h.
* @brief The RenderPassEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::RenderPassEncoder Class.
	* This class defines the WebGPU::Unit::RenderPassEncoder behaves.
	*/
	class RenderPassEncoder : public Unit<WGPURenderPassEncoder>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		RenderPassEncoder() = default;

		/**
		* @brief Destructor Function.
		*/
		~RenderPassEncoder() override;
		
		/**
		* @brief Set Unit name.
		* 
		* @param[in] name Unit name.
		*/
		void SetName(const std::string& name) const;

		/**
		* @brief End RenderPass.
		*/
		void EndRenderPass() const;
		
		/**
		* @brief Begin Occlusion Query.
		*
		* @param[in] queryIndex .
		*/
		void BeginOcclusionQuery(uint32_t queryIndex) const;
		
		/**
		* @brief End Occlusion Query.
		*/
		void EndOcclusionQuery() const;
		
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
		* @param[in] baseVertex .
		* @param[in] firstInstance .
		*/
		void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) const;
		
		/**
		* @brief DrawIndexedIndirect.
		*
		* @param[in] indirectBuffer .
		* @param[in] indirectOffset .
		*/
		void DrawIndexedIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset) const;
		
		/**
		* @brief DrawIndirect.
		*
		* @param[in] indirectBuffer .
		* @param[in] indirectOffset .
		*/
		void DrawIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset) const;
		
		/**
		* @brief ExecuteBundles.
		*
		* @param[in] bundleCount .
		* @param[in] bundles WGPURenderBundle.
		*/
		void ExecuteBundles(size_t bundleCount, const WGPURenderBundle& bundles) const;
		
		/**
		* @brief InsertDebugMarker.
		*
		* @param[in] markerLabel .
		*/
		void InsertDebugMarker(const std::string& markerLabel) const;
		
		/**
		* @brief MultiDrawIndexedIndirect.
		*
		* @param[in] indirectBuffer WGPUBuffer.
		* @param[in] indirectOffset .
		* @param[in] maxDrawCount .
		* @param[in] drawCountBuffer .
		* @param[in] drawCountBufferOffset .
		*/
		void MultiDrawIndexedIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) const;
		
		/**
		* @brief MultiDrawIndirect.
		*
		* @param[in] indirectBuffer WGPUBuffer.
		* @param[in] indirectOffset .
		* @param[in] maxDrawCount .
		* @param[in] drawCountBuffer .
		* @param[in] drawCountBufferOffset .
		*/
		void MultiDrawIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) const;
		
		/**
		* @brief PushDebugGroup.
		*
		* @param[in] groupLabel .
		*/
		void PushDebugGroup(const std::string& groupLabel) const;
		
		/**
		* @brief PopDebugGroup.
		*/
		void PopDebugGroup() const;
		
		/**
		* @brief SetBindGroup.
		* 
		* @param[in] groupIndex .
		* @param[in] group WGPUBindGroup.
		* @param[in] dynamicOffsets .
		*/
		void SetBindGroup(uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsets = 0) const;
		
		/**
		* @brief SetBlendConstant.
		* 
		* @param[in] color WGPUColor.
		*/
		void SetBlendConstant(WGPUColor color) const;
		
		/**
		* @brief SetImmediates.
		* 
		* @param[in] offset .
		* @param[in] data .
		* @param[in] size .
		*/
		void SetImmediates(uint32_t offset, const void* data, size_t size) const;
		
		/**
		* @brief SetIndexBuffer.
		* 
		* @param[in] buffer WGPUBuffer.
		* @param[in] format WGPUIndexFormat.
		* @param[in] offset .
		* @param[in] size .
		*/
		void SetIndexBuffer(WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) const;
		
		/**
		* @brief SetStencilReference.
		* 
		* @param[in] reference .
		*/
		void SetStencilReference(uint32_t reference) const;
		
		/**
		* @brief SetVertexBuffer.
		* 
		* @param[in] slot .
		* @param[in] buffer WGPUBuffer.
		* @param[in] offset .
		* @param[in] size .
		*/
		void SetVertexBuffer(uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) const;
		
		/**
		* @brief WriteTimestamp.
		* 
		* @param[in] querySet WGPUQuerySet.
		* @param[in] queryIndex .
		*/
		void WriteTimestamp(WGPUQuerySet querySet, uint32_t queryIndex) const;
		
		/**
		* @brief Set Viewport.
		*
		* @param[in] x .
		* @param[in] y .
		* @param[in] width .
		* @param[in] height .
		* @param[in] minDepth .
		* @param[in] maxDepth .
		*/
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height, float minDepth, float maxDepth) const;

		/**
		* @brief Set Scissor.
		*
		* @param[in] x .
		* @param[in] y .
		* @param[in] width .
		* @param[in] height .
		*/
		void SetScissor(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const;
		
		/**
		* @brief Set Pipeline.
		*
		* @param[in] pipeline WGPURenderPipeline.
		*/
		void SetPipeline(WGPURenderPipeline pipeline) const;
	};
}

#endif