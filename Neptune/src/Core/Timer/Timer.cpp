/**
* @file Timer.cpp.
* @brief The Timer Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Timer.h"

namespace Neptune {

	Timer::Timer()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_StartTime = std::chrono::steady_clock::now();
		
		m_LastTime  = std::chrono::steady_clock::now();
	}

	void Timer::Flush()
	{
		NEPTUNE_PROFILE_ZONE
		
		const auto nowTime = std::chrono::steady_clock::now();

		m_SegmentTime = std::chrono::duration<float>(nowTime - m_LastTime).count();

		m_DurationTime = std::chrono::duration<float>(nowTime - m_StartTime).count();

		m_LastTime = nowTime;
	}
}