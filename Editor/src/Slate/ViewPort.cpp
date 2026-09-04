/**
* @file ViewPort.cpp.
* @brief The ViewPort Class Implementation.
* @author Spices.
*/

#include "ViewPort.h"
#include <Resource/ResourcePool/ResourcePool.h>
#include <Resource/Texture/RenderTarget.h>
#include <Device/Graphics/Frontend/RHI/RenderTarget.h>
#include <Core/Event/ViewEvent.h>
#include <Core/Event/WindowEvent.h>
#include <Core/Event/EngineEvent.h>

#include <imgui.h>
#include <glm/common.hpp>

namespace Neptune::Editor::View {

	namespace {

		ImTextureID s_TextureID{};
		ImVec2      s_SlateSize = { 1, 1 };
	}

	void ViewPort::OnSubmitRHI()
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui::SetNextWindowBgAlpha(0.5f);

		bool open;
		ImGui::Begin("ViewPort", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);

		ResizeQuery();

		ImGui::Image(s_TextureID, s_SlateSize);

		ImGui::End();
	}

	void ViewPort::ResizeQuery()
	{
		NEPTUNE_PROFILE_ZONE
		
		ImVec2 tempSize = ImVec2(glm::max(ImGui::GetContentRegionAvail().x, 1.0f), glm::max(ImGui::GetContentRegionAvail().y, 1.0f));

		if (s_SlateSize.x != tempSize.x || s_SlateSize.y != tempSize.y)
		{
			{
				EngineEvent event(EngineEventBit::StopTheEngine);

				Dispatch(event);
			}

			{
				ViewResizeEvent event(static_cast<uint32_t>(tempSize.x), static_cast<uint32_t>(tempSize.y));

				Dispatch(event);
			}

			s_TextureID = (ImTextureID)ResourcePool<RenderTarget>::Instance().Access("Scene")->GetRHIResource()->CreateBindingID();
		}

		s_SlateSize = tempSize;
	}

}
