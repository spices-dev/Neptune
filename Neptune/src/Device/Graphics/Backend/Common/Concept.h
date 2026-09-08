/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"

namespace Neptune::Graphic::Common {
    
    /**
    * @brief Concept: Is Unit Handle.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnitHandle = IsPointer<T> || IsIntegral<T> || IntegerWrapper<T>;
    
    /**
    * @brief Concept: Is Unit EUnit.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnitEUnit = std::is_enum_v<T> || IsIntegral<T>;
    
    /**
    * @brief Concept: Is Unit.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsUnit = requires(T t) {
        typename T::Handle;
        t.E_;
        requires IsUnitHandle<typename T::Handle>;
        requires IsUnitEUnit<decltype(T::E_)>;
    };
    
    /**
    * @brief Concept: Is ContextAccessor.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsContextAccessor = requires(T t) {
        typename T::Context;
    };
    
    /**
    * @brief Concept: Is Infrastructure.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsInfrastructure = requires(T t) {
        typename T::ContextAccessor;
        typename T::Context;
    };
    
    /**
    * @brief Concept: Is AInfrastructure.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsAInfrastructure = requires(T t) {
        typename T::T;
        t.E;
        requires IsEnum<decltype(T::E)>;
    };
    
    /**
    * @brief Concept: Is IInfrastructure.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsIInfrastructure = requires(T t) {
        requires IsInfrastructure<typename T::T>;
        requires IsAInfrastructure<T>;
    };
    
    /**
    * @brief Concept: Is ContextElement.
    * 
    * @tparam B .
    * @tparam T .
    */
    template<typename B, typename T>
    concept IsContextElement = IsBase<B, T>;
    
    /**
    * @brief Concept: Is IContextElement.
    * 
    * @tparam B .
    * @tparam T .
    */
    template<typename B, typename T>
    concept IsIContextElement = requires(T t) {
        typename T::T;
        t.E;
        requires IsContextElement<B, typename T::T>;
        requires IsEnum<decltype(T::E)>;
    };
    
    /**
    * @brief Concept: Is Has Static Factory.
    * 
    * @tparam T .
    * @tparam Args .
    */
    template<typename T, typename... Args>
    concept IsHasStaticFactory = requires(Args&&... args)
    {
        { T::Create(std::forward<Args>(args)...) } -> IsSame<UP<T>>;
    };
    
    /**
    * @brief Concept: Is Context Element Buildable.
    * 
    * @tparam Element ContextElement.
    * @tparam T Specification of Element.
    * @tparam C Context.
    * @tparam E EElement.
    * @tparam Args Construct Params.
    */
    template<typename Element, typename T, typename C, typename E, typename... Args>
    concept IsContextElementBuildable = IsContextElement<Element, T> &&
    (
        IsHasStaticFactory<T, C&, E, Args...>      ||   // @brief Factory with     Context and Enum.
        IsHasStaticFactory<T, Args...>             ||   // @brief Factory without  Context and Enum.
        IsConstructible<T, C&, E, Args...>         ||   // @brief Directly with    Context and Enum.
        IsConstructible<T, Args...>                     // @brief Directly without Context and Enum.
    );
}