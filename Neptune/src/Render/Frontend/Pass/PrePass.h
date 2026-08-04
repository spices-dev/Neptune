/**
* @file PrePass.h.
* @brief The PrePass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Pass.h"

#include <glm/vec2.hpp>

namespace Neptune::RHI {

	class DescriptorList;
}

namespace Neptune::Render {

	/**
	* @brief PrePass Class
	*/
	class PrePass : public Pass
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		PrePass() : Pass() {}
		
		/**
		* @brief Destructor Function.
		*/
		~PrePass() override = default;

		/**
		* @brief Interface of Construct.
		*/
		void OnConstruct() override;

		/**
		* @brief Interface of CollectRHI.
		*
		* @param[in] scene Scene.
		*/
		void OnCollectRHI(Scene* scene) override;

		/**
		* @brief Set this Pass FrameBuffer Attachment Size.
		*
		* @param[in] rtSize FrameBuffer Attachment Size.
		*/
		void SetRTSize(const glm::vec2& rtSize) { m_RTSize = rtSize; }

	private:

		SP<RHI::DescriptorList>  m_DescriptorList;                   // @brief DescriptorList
		glm::vec2                m_RTSize{ 100.0f, 100.0f };     // @brief FrameBuffer Attachment Size
	};
}