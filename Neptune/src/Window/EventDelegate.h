/**
* @file EventDelegate.h.
* @brief The EventDelegate Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Delegate/DelegateBasic.h"

#include <any>

namespace Neptune {

    DELEGATE(SlateEvent, const std::any&)
    
    /**
    * @brief Delegate for Event.
    */
    struct EventDelegate
    {
        DelegateSlateEvent onSlateEvent;      // @brief Delegate of Slate Event.
    };
    
}