/**
* @file Capability.h.
* @brief The Capability Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Device/Graphics/Frontend/Enum.h"

namespace Neptune::RHI {

	using RHICapability = RHI<ERHI::Capability>;

	/**
	* @brief Specialization of RHICapability::Impl
	*/
	template<>
	class RHICapability::Impl : public RHIImplEmpty
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
		* @brief Is Capability Support.
		* 
		* @param[in] capability Graphic::ECapability.
		* 
		* @return Returns true if succeeded.
		*/
		virtual bool IsSupport(Graphic::ECapability capability) = 0;
		
		/**
		* @brief Is Pipeline Support.
		* 
		* @param[in] capability Graphic::EPipeline.
		* 
		* @return Returns true if succeeded.
		*/
		virtual bool IsSupport(Graphic::EPipeline capability) = 0;
		
		/**
		* @brief Is Shader Support.
		* 
		* @param[in] capability Graphic::EShader.
		* 
		* @return Returns true if succeeded.
		*/
		virtual bool IsSupport(Graphic::EShader capability) = 0;
		
		/**
		* @brief Is Query Support.
		* 
		* @param[in] capability Graphic::EQuery.
		* 
		* @return Returns true if succeeded.
		*/
		virtual bool IsSupport(Graphic::EQuery capability) = 0;
	};

	/**
	* @brief RHI of ERHI::Capability
	*/
	class Capability : public RHICapability
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Capability() = default;

		/**
		* @brief Destructor Function.
		*/
		~Capability() override = default;
		
		/**
		* @brief Is Capability Support.
		* 
		* @param[in] capability Graphic::ECapability.
		* 
		* @return Returns true if succeeded.
		*/
		bool IsSupport(Graphic::ECapability capability) const { return m_Impl->IsSupport(capability); }
		
		/**
		* @brief Is Pipeline Support.
		* 
		* @param[in] capability Graphic::EPipeline.
		* 
		* @return Returns true if succeeded.
		*/
		bool IsSupport(Graphic::EPipeline capability) const { return m_Impl->IsSupport(capability); }
		
		/**
		* @brief Is Shader Support.
		* 
		* @param[in] capability Graphic::EShader.
		* 
		* @return Returns true if succeeded.
		*/
		bool IsSupport(Graphic::EShader capability) const { return m_Impl->IsSupport(capability); }
		
		/**
		* @brief Is Query Support.
		* 
		* @param[in] capability Graphic::EQuery.
		* 
		* @return Returns true if succeeded.
		*/
		bool IsSupport(Graphic::EQuery capability) const { return m_Impl->IsSupport(capability); }
	};
}