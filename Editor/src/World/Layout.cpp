/**
* @file Layout.cpp.
* @brief The Layout Namespace Implementation.
* @author Spices.
*/

#include "Layout.h"
#include "Slate/Console.h"

namespace Neptune::Editor::Layout {

    using namespace View;
    
    void OnLayout()
    {
        Console console;
        
        console.OnSubmitRHI();
    }
    
}