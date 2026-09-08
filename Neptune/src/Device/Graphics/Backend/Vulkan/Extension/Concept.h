/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"
#include "Device/Graphics/Backend/Common/Context/Context.h"
#include "Extension.h"

namespace Neptune::Vulkan::Extension {
    
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