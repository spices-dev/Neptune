/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"
#include "Layer.h"

namespace Neptune::Vulkan::Layer {
    
    /**
    * @brief Concept: Is Layer.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsLayer = IsBase<Layer, T>;
    
    /**
    * @brief Concept: Is ILayer.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsILayer = requires(T t) {
        typename T::T;
        t.E;
        requires IsLayer<typename T::T>;
        requires IsEnum<decltype(T::E)>;
    };
    
}