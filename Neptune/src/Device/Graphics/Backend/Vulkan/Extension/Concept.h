/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"
#include "Extension.h"

namespace Neptune::Vulkan::Extension {
    
    /**
    * @brief Concept: Is Extension.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsExtension = IsBase<Extension, T>;
    
    /**
    * @brief Concept: Is IExtension.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsIExtension = requires(T t) {
        typename T::T;
        t.E;
        requires IsExtension<typename T::T>;
        requires IsEnum<decltype(T::E)>;
    };
    
    /**
    * @brief Concept: Is IsCoreExtension.
    * 
    * @tparam T IsExtension.
    */
    template<typename T>
    static constexpr bool IsCoreExtension = requires(T t) {
        t.CoreVersion;
        requires IsExtension<RemoveRef<T>>;
        requires VK_VERSION >= t.CoreVersion;
    };
    
}