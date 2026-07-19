/**
* @file SlateFrontend.cpp.
* @brief The SlateFrontend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SlateFrontend.h"
#include "Slate/Backend/ImGui/SlateBackend.h"

namespace Neptune {

	UP<SlateFrontend> SlateFrontend::Create(SlateBackendEnum slateBackend, RenderBackendEnum renderBackend, WindowImplement windowImpl)
	{
        NEPTUNE_PROFILE_ZONE

		UP<SlateFrontend> sp = nullptr;

		switch (slateBackend)
		{
            case SlateBackendEnum::ImGui: sp = CreateUP<imgui::SlateBackend>(renderBackend, windowImpl); break;
            default:
            {
                NEPTUNE_CORE_CRITICAL("Not Supported Slate Backend.")
                return nullptr;
            }
		}

        return sp;
	}

    SlateFrontend::~SlateFrontend() = default;

    SlateFrontend::SlateFrontend(SlateBackendEnum backend) : m_SlateBackendEnum(backend) {}

}