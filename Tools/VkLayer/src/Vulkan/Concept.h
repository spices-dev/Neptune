/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once

#include <concepts>

namespace Neptune::Vulkan {
    
    /**
    * @brief Using: Decay.
    * 
    * @tparam T .
    */
    template<typename T>
    using Decay = std::decay_t<T>;
    
    /**
    * @brief Concept: Is Pointer.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsPointer = std::is_pointer_v<T>;
    
    /**
    * @brief Concept: Is Integral.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsIntegral = std::is_integral_v<T>;
    
    /**
    * @brief Concept: Is Void.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsVoid = std::is_void_v<T>;
    
    /**
    * @brief Concept: Is Enum.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsEnum = std::is_enum_v<T> && requires {
        { T::Count } -> std::convertible_to<T>;
    };
    
    /**
    * @brief Concept: Is Empty Enum.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsEmptyEnum = IsEnum<T> && requires {
        { T::Count } -> std::convertible_to<T>;
        requires std::bool_constant<static_cast<uint32_t>(T::Count) == 0>::value;
    };
    
    /**
    * @brief Concept: Is Not Empty Enum.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsNotEmptyEnum = IsEnum<T> && !IsEmptyEnum<T>;
    
    /**
    * @brief Concept: Is FunctionPointer.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsFunctionPointer = IsPointer<T> && std::is_function_v<std::remove_pointer_t<T>>;
    
    /**
    * @brief Concept: Is UnitLifeFunction.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnitLifeFunction = IsFunctionPointer<T> || IsVoid<T>;
    
    /**
    * @brief Concept: Is Unit Handle.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnitHandle = IsPointer<T> || IsIntegral<T>;
    
    /**
    * @brief Concept: Is EInfrastructure.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsEInfrastructure = IsNotEmptyEnum<T> || IsIntegral<T>;
    
    /**
    * @brief Concept: Is IInfrastructure.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsIInfrastructure = requires(T t) {
        typename T::T;
        t.E;
        requires IsEInfrastructure<decltype(T::E)>;
    };
    
}