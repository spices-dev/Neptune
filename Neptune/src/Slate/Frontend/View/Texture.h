#pragma once
#include "Core/Core.h"
#include "ViewBase.h"
#include "Slate/Frontend/ViewState/Texture.h"

namespace Neptune::View {

	class Texture : public ViewBase
	{
	public:

		static Texture Create(ViewState::Texture state);

		Texture() : ViewBase() {}

		~Texture() override = default;

		

	private:

		void ResizeQuery();

	};

}