/**
* @file Layout.cpp.
* @brief The Layout Namespace Implementation.
* @author Spices.
*/

#include "Layout.h"
#include "Slate/Console.h"
#include "Slate/ViewPort.h"

namespace Neptune::Editor::Layout {

    using namespace View;
    
    std::function<void()> OnLayout()
    {
        NEPTUNE_PROFILE_ZONE
        
        Console console;
            
        console.OnSubmitRHI();
            
        ViewPort viewPort;
        
        viewPort.OnSubmitRHI();
    }
    
}