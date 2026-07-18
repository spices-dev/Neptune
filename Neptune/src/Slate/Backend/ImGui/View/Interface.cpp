/**
* @file Interface.cpp.
* @brief The Interface Namespace Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Slate/Frontend/View/Interface.h"

#include <imgui.h>

namespace Neptune::View::Interface {

    void ShowDemoWindow()
    {
        NEPTUNE_PROFILE_ZONE
        
        ImGui::ShowDemoWindow();
    }

}
