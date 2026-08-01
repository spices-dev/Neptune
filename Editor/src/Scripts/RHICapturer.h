/**
* @file RHICapturer.h.
* @brief The RHICapturer Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <Scripts/NativeScripts/NativeScript.h>
#include <Core/Event/KeyEvent.h>

namespace Neptune::Editor {
	
	/**
	* @brief RHICapturer Script.
	*/
	class RHICapturer : public NativeScript
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		RHICapturer() = default;
		
		/**
		* @brief Destructor Function.
		*/
		~RHICapturer() override = default;

		/**
		* @brief This interface defines the behave on specific component event happened.
		*
		* @param[in] e Event.
		*/
		void OnEvent(Event& e) override;

	private:

		/**
		* @brief Key Pressed Event.
		*
		* @param[in] e KeyPressedEvent.
		*
		* @return Returns true if consumed.
		*/
		bool OnKeyPressedEvent(KeyPressedEvent& e) const;

	};
}