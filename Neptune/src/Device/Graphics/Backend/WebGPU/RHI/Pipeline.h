/**
* @file Pipeline.h.
* @brief The Pipeline Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Resource/Pipeline.h"
#include "Device/Graphics/Backend/WebGPU/Unit/PipelineLayout.h"
#include "Device/Graphics/Frontend/RHI/Pipeline.h"

namespace Neptune::RHI {

	class RenderPass;
	class DescriptorList;
	class Shader;
}

namespace Neptune::WebGPU {

	/**
	* @brief WebGPU::Pipeline Class.
	* This class defines the WebGPU::Pipeline behaves.
	*/
	class Pipeline : public ContextAccessor, public RHI::RHIPipeline::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Pipeline(Context& context) : ContextAccessor(context), m_Pipeline(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Pipeline() override = default;

	public:

		/**
		* @brief Interface of Set Default Pipeline.
		*/
		void SetDefault() override;

		/**
		* @brief Interface of Set RenderPass.
		*
		* @param[in] renderPass RenderPass.
		*/
		void SetRenderPass(const SP<RHI::RenderPass>& renderPass) override {}
		
		/**
		* @brief Interface of Set DescriptorList.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		void SetDescriptorList(const SP<RHI::DescriptorList>& descriptorList) override;

		/**
		* @brief Interface of Set VertexAttributeLayout.
		*/
		void SetVertexAttributeLayout() override;
		
		/**
		* @brief Interface of Set CullMode.
		*
		* @param[in] mode ECullMode.
		*/
		void SetCullMode(ECullMode mode) override;

		/**
		* @brief Interface of Set Topology.
		* 
		* @param[in] topology ETopology.
		*/
		void SetTopology(ETopology topology) override;

		/**
		* @brief Interface of Add Shader.
		*
		* @param[in] stage ShaderStage.
		* @param[in] shader Shader.
		*/
		void AddShader(ShaderStage stage, const SP<RHI::Shader>& shader) override;

		/**
		* @brief Interface of Build GraphicPipeline.
		*/
		void BuildGraphicPipeline() override;

		/**
		* @brief Interface of Build ComputePipeline.
		*/
		void BuildComputePipeline() override;
		
	public:

		/**
		* @brief Get PipelineLayout Unit Handle.
		*
		* @return Returns PipelineLayout Unit Handle.
		*/
		const Unit::PipelineLayout::Handle& GetPipelineLayout() const { return m_PipelineLayout.GetHandle(); }

		/**
		* @brief Get Pipeline Unit Handle.
		*
		* @tparam T Pipeline Unit
		* 
		* @return Returns Pipeline Unit Handle.
		*/
		template<IsUnit T>
		T::Handle Handle() const { return m_Pipeline.Handle<T>(); }
		
	private:
		
		Resource::Pipeline                m_Pipeline;               // @brief Pipeline.
		Unit::PipelineLayout              m_PipelineLayout;         // @brief PipelineLayout.
		WGPUVertexState                   m_VertexState{};          // @brief WGPUVertexState.
		WGPUFragmentState                 m_FragmentState{};        // @brief WGPUFragmentState.
		WGPUComputeState                  m_ComputeState{};         // @brief WGPUComputeState.
		     
		WGPUMultisampleState              m_MultisampleState{};     // @brief WGPUMultisampleState.
		WGPUPrimitiveState                m_PrimitiveState{};       // @brief WGPUPrimitiveState.
		WGPUDepthStencilState             m_DepthStencilState{};    // @brief WGPUDepthStencilState.
	};
}

#endif