/**
* @file ViewPort.h.
* @brief The ViewPort Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <Slate/Frontend/View/ViewBase.h>

namespace Neptune::Editor::View {

	class ViewPort : public Neptune::View::ViewBase
	{
	public:

		ViewPort() = default;

		~ViewPort() override = default;

		void OnSubmitRHI();
		
	private:

		void ResizeQuery();
	};

}