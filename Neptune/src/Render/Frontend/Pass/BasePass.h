/**
* @file BasePass.h.
* @brief The BasePass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Pass.h"
#include <glm/vec2.hpp>

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
}

namespace Neptune::Render { 

	/**
	* @brief BasePass Class
	*/
	class BasePass : public Pass
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		BasePass() : Pass() {}
		
		/**
		* @brief Destructor Function.
		*/
		~BasePass() override = default;

		/**
		* @brief Interface of Construct.
		*/
		void OnConstruct() override;

		/**
		* @brief Interface of CollectRHI.
		*
		* @param[in] scene Scene.
		*/
		void OnCollectRHI(Scene* scene, RHI::CmdList& cmdList) override;

		/**
		* @brief Set this Pass FrameBuffer Attachment Size.
		*
		* @param[in] rtSize FrameBuffer Attachment Size.
		*/
		void SetRTSize(const glm::vec2& rtSize) { m_RTSize = rtSize; }

	private:

		SP<RHI::RenderPass>      m_RenderPass;                     // @brief RenderPass
		SP<RHI::DescriptorList>  m_DescriptorList;                 // @brief DescriptorList
		SP<RHI::Pipeline>        m_Pipeline;                       // @brief Pipeline
		glm::vec2                m_RTSize{ 100.0f, 100.0f };   // @brief FrameBuffer Attachment Size
	};
}