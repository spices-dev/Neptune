/**
* @file Pipeline.h.
* @brief The Pipeline Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Asset/SOP/Enum.h"
#include "Resource/Shader/Shader.h"
#include "RHI.h"

namespace Neptune::RHI {

	using RHIPipeline = RHI<ERHI::Pipeline>;

	/**
	* @brief Specialization of RHIPipeline::Impl
	*/
	template<>
	class RHIPipeline::Impl
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

		/**
		* @brief Interface of Set Default Pipeline.
		*/
		virtual void SetDefault() = 0;

		/**
		* @brief Interface of Set RenderPass.
		* 
		* @param[in] renderPass RenderPass.
		*/
		virtual void SetRenderPass(const SP<class RenderPass>& renderPass) = 0;

		/**
		* @brief Interface of Set DescriptorList.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		virtual void SetDescriptorList(const SP<class DescriptorList>& descriptorList) = 0;

		/**
		* @brief Interface of Set VertexAttributeLayout.
		*/
		virtual void SetVertexAttributeLayout() = 0;

		/**
		* @brief Interface of Set CullMode.
		* 
		* @param[in] mode ECullMode.
		*/
		virtual void SetCullMode(ECullMode mode) = 0;

		/**
		* @brief Interface of Set Topology.
		* 
		* @param[in] topology ETopology.
		*/
		virtual void SetTopology(ETopology topology) = 0;

		/**
		* @brief Interface of Add Shader.
		*
		* @param[in] stage ShaderStage.
		* @param[in] shader Shader.
		*/
		virtual void AddShader(ShaderStage stage, const SP<class Shader>& shader) = 0;

		/**
		* @brief Interface of Build GraphicPipeline.
		*/
		virtual void BuildGraphicPipeline() = 0;
		
		/**
		* @brief Interface of Build ComputePipeline.
		*/
		virtual void BuildComputePipeline() = 0;
	};

	/**
	* @brief RHI of ERHI::Pipeline
	*/
	class Pipeline : public RHIPipeline
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Pipeline() = default;

		/**
		* @brief Destructor Function.
		*/
		~Pipeline() override = default;

		/**
		* @brief Interface of Set Default Pipeline.
		*/
		void SetDefault() const { RHIPipeline::m_Impl->SetDefault(); }

		/**
		* @brief Interface of Set RenderPass.
		*
		* @param[in] renderPass RenderPass.
		*/
		void SetRenderPass(const SP<class RenderPass>& renderPass) const { m_Impl->SetRenderPass(renderPass); }

		/**
		* @brief Interface of Set DescriptorList.
		*
		* @param[in] descriptorList DescriptorList.
		*/
		void SetDescriptorList(const SP<class DescriptorList>& descriptorList) const { m_Impl->SetDescriptorList(descriptorList); }

		/**
		* @brief Interface of Set VertexAttributeLayout.
		*/
		void SetVertexAttributeLayout() const { m_Impl->SetVertexAttributeLayout(); }

		/**
		* @brief Interface of Set CullMode.
		*
		* @param[in] mode ECullMode.
		*/
		void SetCullMode(ECullMode mode) const { m_Impl->SetCullMode(mode); }

		/**
		* @brief Interface of Set Topology.
		* 
		* @param[in] topology ETopology.
		*/
		void SetTopology(ETopology topology) const { m_Impl->SetTopology(topology); }

		/**
		* @brief Interface of Add Shader.
		*
		* @param[in] stage ShaderStage.
		* @param[in] shader Shader.
		*/
		void AddShader(ShaderStage stage, const SP<class Shader>& shader) const { m_Impl->AddShader(stage, shader); }

		/**
		* @brief Interface of Build GraphicPipeline.
		*/
		void BuildGraphicPipeline() const { m_Impl->BuildGraphicPipeline(); }
		
		/**
		* @brief Interface of Build ComputePipeline.
		*/
		void BuildComputePipeline() const { m_Impl->BuildComputePipeline(); }

	};

	
}