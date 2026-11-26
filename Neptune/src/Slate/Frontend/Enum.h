/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief Enum of Slate Backend.
    */
    enum class SlateBackendEnum : uint8_t
    {
        None = 0,
        ImGui,

        Count
    };

    /**
    * @brief Enum of Presenter.
    */
    enum class EPresenter : uint8_t
    {
        P0 = 0,             // @brief Position 0, and so on.
        P1,
        P2,
        P3,
        P4,
        P5,
        P6,
        P7,
        P8,
        P9,
        
        // ....
        
        Count,
    };
    
}