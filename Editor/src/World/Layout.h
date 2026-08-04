/**
* @file Layout.h.
* @brief The Layout Namespace Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>

#include <functional>

namespace Neptune::Editor::Layout {

    std::function<void()> OnLayout();
    
}