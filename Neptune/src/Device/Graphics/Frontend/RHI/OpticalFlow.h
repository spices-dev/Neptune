/**
* @file OpticalFlow.h.
* @brief The OpticalFlow Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace Neptune::RHI {

	class RenderTarget;

	using RHIOpticalFlow = RHI<ERHI::OpticalFlow>;

	/**
	* @brief Specialization of RHIOpticalFlow::Impl
	*/
	template<>
	class RHIOpticalFlow::Impl
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
		* @brief Interface of Set Input RenderTarget.
		* 
		* @param[in] rt RenderTarget.
		*/
		virtual void SetInputRenderTarget(const SP<RenderTarget>& rt) = 0;

		/**
		* @brief Interface of Set Reference RenderTarget.
		*
		* @param[in] rt RenderTarget.
		*/
		virtual void SetReferenceRenderTarget(const SP<RenderTarget>& rt) = 0;

		/**
		* @brief Interface of Set FlowVector RenderTarget.
		*
		* @param[in] rt RenderTarget.
		*/
		virtual void SetFlowVectorRenderTarget(const SP<RenderTarget>& rt) = 0;

		/**
		* @brief Interface of Create OpticalFlow Session.
		* 
		* @return Returns true if succeeded.
		*/
		virtual bool CreateOpticalFlowSession() = 0;

		/**
		* @brief Interface of OpticalFlow Execute.
		*/
		virtual void OpticalFlowExecute() = 0;
	};

	/**
	* @brief RHI of ERHI::OpticalFlow
	*/
	class OpticalFlow : public RHIOpticalFlow
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		OpticalFlow() = default;

		/**
		* @brief Destructor Function.
		*/
		~OpticalFlow() override = default;

		/**
		* @brief Interface of Set Input RenderTarget.
		*
		* @param[in] rt RenderTarget.
		*/
		void SetInputRenderTarget(const SP<RenderTarget>& rt) const { m_Impl->SetInputRenderTarget(rt); }

		/**
		* @brief Interface of Set Reference RenderTarget.
		*
		* @param[in] rt RenderTarget.
		*/
		void SetReferenceRenderTarget(const SP<RenderTarget>& rt) const { m_Impl->SetReferenceRenderTarget(rt); }

		/**
		* @brief Interface of Set FlowVector RenderTarget.
		*
		* @param[in] rt RenderTarget.
		*/
		void SetFlowVectorRenderTarget(const SP<RenderTarget>& rt) const { m_Impl->SetFlowVectorRenderTarget(rt); }

		/**
		* @brief Interface of Create OpticalFlow Session.
		* 
		* @return Returns true if succeeded.
		*/
		bool CreateOpticalFlowSession() const { return m_Impl->CreateOpticalFlowSession(); }

		/**
		* @brief Interface of OpticalFlow Execute.
		*/
		void OpticalFlowExecute() const { m_Impl->OpticalFlowExecute(); }
	};
}