/**
* @file Console.cpp.
* @brief The Console Class Implementation.
* @author Spices.
*/

#include "Console.h"
#include "Slate/Frontend/View/Interface.h"

namespace Neptune::Editor::View {
    
    using namespace Neptune::View::Interface;
    
    void Console::OnSubmitRHI()
    {
        NEPTUNE_PROFILE_ZONE
        
        ShowDemoWindow();
    }
}
