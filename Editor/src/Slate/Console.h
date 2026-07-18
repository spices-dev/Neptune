/**
* @file Console.h.
* @brief The Console Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include "Panel.h"

namespace Neptune::Editor::View {
    
    class Console : public Panel
    {
    public:

        Console() = default;

        ~Console() override = default;
        
        void OnSubmitRHI();
        
    };
    
}
