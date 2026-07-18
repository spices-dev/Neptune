/**
* @file ViewBase.h.
* @brief The ViewBase Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"
#include "Core/Delegate/DelegateBasic.h"

namespace Neptune::View {

    DELEGATE(OnClick)
    DELEGATE(OnMouseHover)
    DELEGATE(OnMouseMove)

    /**
    * @brief This Class defines the basic behaves of specific slate.
    * When we add a new Slate, we need inherit from this.
    */
    class ViewBase
    {
    public:

        /**
        * @brief Constructor Function.
        */
        ViewBase() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~ViewBase() = default;

        DelegateOnClick      onClick;
        DelegateOnMouseHover onMouseHover;
        DelegateOnMouseMove  onMouseMove;
    };
}
