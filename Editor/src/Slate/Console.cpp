/**
* @file Console.cpp.
* @brief The Console Class Implementation.
* @author Spices.
*/

#include "Console.h"

#include <imgui.h>

namespace Neptune::Editor::View {
    
    void Console::OnSubmitRHI()
    {
        NEPTUNE_PROFILE_ZONE
        
        ImGui::ShowDemoWindow();
    }
}
