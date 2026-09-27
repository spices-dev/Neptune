/**
* @file TimeLine.h.
* @brief The TimeLine Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/OpenGL/Unit/Sync.h"

namespace Neptune::OpenGL {

	using ITimeLine = IInfrastructure<class TimeLine, EInfrastructure::TimeLine>;

	/**
	* @brief OpenGL::TimeLine Class.
	* This class defines the OpenGL::TimeLine behaves.
	*/
	class TimeLine : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count Fence count.
		*/
		TimeLine(Context& context, EInfrastructure e, uint32_t count = 1);

		/**
		* @brief Destructor Function.
		*/
		~TimeLine() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @param[in] index Fence index.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::Sync::Handle& Handle(uint32_t index = 0) const { return m_Fences[index]->GetHandle(); }

		/**
		* @brief Fence wait idle.
		* 
		* @param[in] frameId FrameId.
		*/
		void Wait(uint32_t frameId) const;

		/**
		* @brief Fence Signal.
		* 
		* @param[in] frameId FrameId.
		*/
		void Signal(uint32_t frameId);

	private:

		/**
		* @brief Create Fence.
		* 
		* @param[in] count Fence count.
		*/
		void Create(uint32_t count);

	private:

		std::vector<UP<Unit::Sync>> m_Fences; // @brief Container of this Fence.

	};
	
}

#endif