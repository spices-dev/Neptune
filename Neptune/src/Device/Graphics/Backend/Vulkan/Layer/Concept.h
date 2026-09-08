/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"
#include "Device/Graphics/Backend/Common/Context/Context.h"
#include "Layer.h"

namespace Neptune::Vulkan::Layer {
    
    /**
    * @brief Concept: Is Layer.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsLayer = Graphic::Common::IsContextElement<Layer, T>;
    
    /**
    * @brief Concept: Is ILayer.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsILayer = Graphic::Common::IsIContextElement<Layer, T>;
    
}