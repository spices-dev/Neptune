/**
* @file ViewPort.h.
* @brief The ViewPort Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <Slate/Frontend/View/ViewBase.h>
#include <Core/Event/EventProducer.h>

namespace Neptune::Editor::View {

	class ViewPort : public Neptune::View::ViewBase, public EventProducer
	{
	public:

		ViewPort() : EventProducer(EventType::Count) {}

		~ViewPort() override = default;

		void OnSubmitRHI();
		
	private:

		void ResizeQuery();
	};

}