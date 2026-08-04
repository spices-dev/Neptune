/**
* @file ViewBase.h.
* @brief The ViewBase Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"
#include "Slate/Frontend/Delegate.h"

namespace Neptune::View {

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

        /**
        * @brief On ViewBase Execute.
        */
        virtual void OnExecute();
        
        DelegateOnMouseTrigger  onMouseTrig;   // @brief DelegateOnMouseTrigger
        DelegateOnKeyTrigger    onKeyTrig;     // @brief DelegateOnKeyTrigger
        DelegateOnViewTrigger   onViewTrig;    // @brief DelegateOnViewTrigger
        
    private:
        
        std::vector<UP<ViewBase>> m_Child;

    };
}
