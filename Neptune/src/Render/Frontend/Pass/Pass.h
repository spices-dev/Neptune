/**
* @file Pass.h.
* @brief The Pass Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Frontend/Core.h"

namespace Neptune {

	class Scene;
}

namespace Neptune::RHI {

	class CmdList;
}

namespace Neptune::Render { 

	/**
	* @brief InFlightResource Template.
	*/
	template<typename T>
	class InFlightResource
	{
	public:
		
		/**
		* @brief Constructor Function.
		*/
		InFlightResource() = default;
		
		/**
		* @brief Destructor Function.
		*/
		virtual ~InFlightResource() = default;
		
		/**
		* @brief Get InFlight Resource.
		* 
		* @param index Frame Index.
		* 
		* @return Returns InFlight Resource.
		*/
		SP<T>& Get(uint32_t index) { return m_Resources[index]; }
		
	private:
		
		std::array<SP<T>, MaxFrameInFlight> m_Resources;
	};
	
	/**
	* @brief Pass Class.
	*/
	class Pass
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Pass() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Pass() = default;

		/**
		* @brief Interface of Construct.
		*/
		virtual void OnConstruct() = 0;

		/**
		* @brief Interface of CollectRHI.
		*
		* @param[in] scene Scene.
		* @param[in] cmdList RHI::CmdList.
		*/
		virtual void OnCollectRHI(Scene* scene, RHI::CmdList& cmdList) = 0;
	};
}