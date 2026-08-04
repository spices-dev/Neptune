#pragma once
#include "Core/Core.h"
#include "ViewBase.h"
#include "Slate/Frontend/ViewModel/Texture.h"

namespace Neptune::View {

	class Texture : public ViewBase
	{
	public:

		static Texture Create(ViewModel::Texture state);

		Texture() : ViewBase() {}

		~Texture() override = default;

	};

}