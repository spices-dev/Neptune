/**
* @file EngineClock.h.
* @brief The EngineClock Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "NativeScript.h"

namespace Neptune {

	namespace Data {
		
		struct Clock;
	}

	/**
	* @brief EngineClock Script Class.
	*/
	class EngineClock : public NativeScript
	{
	public:

		/**
		* @brief Destructor Function.
		* 
		* @param[in] scene Scene.
		*/
		explicit EngineClock(class Scene* scene);
		
		/**
		* @brief Destructor Function.
		*/
		~EngineClock() override;

		/**
		* @brief This interface defines to behave on specific component on attached.
		*/
		void OnAttached() override;
		
		/**
		* @brief This interface defines the behave on specific component tick every frame.
		*/
		void OnTick() override;

	private:

		Scene* m_Scene = nullptr;            // @brief Scene.
		Data::Clock* m_Clock = nullptr;      // @brief Clock.
		UP<class Timer> m_Timer = nullptr;   // @brief Timer.
	};
}