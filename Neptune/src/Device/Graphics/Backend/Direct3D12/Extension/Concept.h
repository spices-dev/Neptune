/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Concept.h"
#include "Device/Graphics/Backend/Common/Context/Context.h"
#include "Extension.h"

namespace Neptune::Direct3D12::Extension {
    
    /**
    * @brief Concept: Is Extension.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsExtension = Graphic::Common::IsContextElement<Extension, T>;
    
    /**
    * @brief Concept: Is IExtension.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsIExtension = Graphic::Common::IsIContextElement<Extension, T>;
    
}

#endif