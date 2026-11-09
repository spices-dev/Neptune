/**
* @file FPSPass.h.
* @brief The FPSPass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Pass.h"

namespace Neptune::RHI {

	class RenderPass;
	class Pipeline;
	class DescriptorList;
}

namespace Neptune::Render { 

	/**
	* @brief FPSPass Class
	*/
	class FPSPass : public Pass
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		FPSPass() : Pass() {}
		
		/**
		* @brief Destructor Function.
		*/
		~FPSPass() override = default;

		/**
		* @brief Interface of Construct.
		*/
		void OnConstruct() override;

		/**
		* @brief Interface of CollectRHI.
		*
		* @param[in] scene Scene.
		* @param[in] cmdList RHI::CmdList.
		*/
		void OnCollectRHI(Scene* scene, RHI::CmdList& cmdList) override;

	private:

		SP<RHI::RenderPass>      m_RenderPass;         // @brief RenderPass
		SP<RHI::DescriptorList>  m_DescriptorList;     // @brief DescriptorList
		SP<RHI::Pipeline>        m_Pipeline;           // @brief Pipeline
	};
}