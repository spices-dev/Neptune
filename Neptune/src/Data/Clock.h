/**
* @file Clock.h.
* @brief The Clock Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::Data {

	/**
	* @brief Engine Clock.
	*/
	struct Clock
	{
		uint32_t m_FrameIndex = 0;         // @brief Flight Frame Index.
		uint32_t m_ImageIndex = 0;         // @brief Swapchain image Index.
		uint32_t m_FrameId    = 1;         // @brief Frame Id.
		float    m_FrameTime  = 0.0f;      // @brief Frame Run Time.
		float    m_EngineTime = 0.0f;      // @brief Engine Run Time.
	};
}