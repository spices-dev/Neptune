/**
* @file Panel.h.
* @brief The Panel Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <Slate/Frontend/View/ViewBase.h>

namespace Neptune::Editor::View {
    
    class Panel : public Neptune::View::ViewBase
    {
    public:

        Panel() = default;

        ~Panel() override = default;
        
    };
    
}