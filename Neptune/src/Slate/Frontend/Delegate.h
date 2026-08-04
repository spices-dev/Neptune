/**
* @file Delegate.h.
* @brief The Delegate Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Delegate/DelegateBasic.h"

namespace Neptune::View {
    
    // @brief Mouse Delegate
    DELEGATE(OnMouseTrigger)

    // @brief Key Delegate
    DELEGATE(OnKeyTrigger)
    
    // @brief View Delegate
    DELEGATE(OnViewTrigger)

}