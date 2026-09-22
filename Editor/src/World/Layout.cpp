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
            
#ifdef NP_PLATFORM_WINDOWS
        
        ViewPort viewPort;
        
        viewPort.OnSubmitRHI();
        
#endif
        
        return [](){};
    }
    
}