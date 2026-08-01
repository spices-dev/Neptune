/**
* @file RHICapturer.cpp.
* @brief The RHICapturer Class Implementation.
* @author Spices.
*/

#include "RHICapturer.h"

namespace Neptune::Editor {
	
	void RHICapturer::OnEvent(Event& e)
	{
		NEPTUNE_PROFILE_ZONE
		
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(RHICapturer::OnKeyPressedEvent));
	}

	bool RHICapturer::OnKeyPressedEvent(KeyPressedEvent& e) const
	{
		NEPTUNE_PROFILE_ZONE

		if (e.GetKeyCode() == Key::F12)
		{
			NEPTUNE_INFO("RHICapturer::F12 Pressed, Execute TriggerCapture() here.")
		}

		return false;
	}

}