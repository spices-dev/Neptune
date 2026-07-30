#pragma once
#include <Core/Core.h>
#include <Slate/Frontend/View/ViewBase.h>

#include <imgui.h>

namespace Neptune::Editor::View {

	class ViewPort : public Neptune::View::ViewBase
	{
	public:

		ViewPort() = default;

		~ViewPort() override = default;

		void OnSubmitRHI();
		
	private:

		void ResizeQuery();

	private:

		ImTextureID m_TextureID{};
		ImVec2      m_SlateSize = { 1, 1 };
	};

}