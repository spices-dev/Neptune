/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include <concepts>
#include <type_traits>
#include <utility>
#include <tuple>

namespace Neptune {
    
    namespace detail {
        
        /**
        * @brief Extract Member from Wrapper using structured bindings.
        * 
        * @param t T.
        * 
        * @return Returns Member.
        */
        template<typename T>
        auto ExtractWrapperMember(T& t) -> decltype(auto)
        {
            auto&& [m] = t;
            
            return (m);
        }
        
        /**
        * @brief Trait of Wrapper.
        * 
        * @tparam T .
        */
        template<typename T, typename = void>
        struct WrapperMemberTypeTrait
        {
            using type = void;
        };

        /**
        * @brief Trait of Wrapper.
        * 
        * @tparam T .
        */
        template<typename T>
        struct WrapperMemberTypeTrait<T, std::void_t<decltype(ExtractWrapperMember(std::declval<T&>()))>>
        {
            using type = std::remove_cvref_t<decltype(ExtractWrapperMember(std::declval<T&>()))>;
        };

        /**
        * @brief Wrapper MemberType.
        * 
        * @tparam T .
        */
        template<typename T>
        using WrapperMemberType = typename WrapperMemberTypeTrait<T>::type;
        
        /**
        * @brief is_tuple base.
        * 
        * @tparam T .
        */
        template <typename T>
        struct is_tuple : std::false_type {};

        /**
        * @brief is_tuple true type.
        * 
        * @tparam T .
        */
        template <typename... T>
        struct is_tuple<std::tuple<T...>> : std::true_type {};

    }
    
    /**
    * @brief Concept: Is Base of.
    * 
    * @tparam B Base Class.
    * @tparam D Derived Class.
    */
    template<typename B, typename D>
    concept IsBase = std::is_base_of_v<B, D>;

    /**
    * @brief Concept: Is Same as.
    * 
    * @tparam T1 One Class.
    * @tparam T2 Another Class.
    */
    template<typename T1, typename T2>
    concept IsSame = std::same_as<T1, T2>;
    
    /**
    * @brief Concept: Is Convertible to.
    * 
    * @tparam T1 One Class.
    * @tparam T2 Another Class.
    */
    template<typename T1, typename T2>
    concept IsConvertible = std::is_convertible_v<T1, T2>;
    
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
    * @brief Concept: Is Tuple.
    * 
    * @tparam T .
    */
    template <typename T>
    concept IsTuple = detail::is_tuple<T>::value;
    
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
    * @brief Concept: Is Class.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsClass = std::is_class_v<T>;
    
    /**
    * @brief Concept: Is Constructable.
    * 
    * @tparam T .
    */
    template<typename T, typename... Args>
    concept IsConstructible = std::constructible_from<T, Args...>;
    
    /**
    * @brief Concept: Is Wrapper of MemberType.
    * 
    * @tparam T .
    * @tparam MemberType Wrapper Type.
    */
    template<typename T, typename MemberType>
    concept IsWrapperOf = 
        std::is_standard_layout_v<T> &&
        std::is_trivially_copyable_v<T> &&
        std::is_aggregate_v<T> &&
        (sizeof(T) == sizeof(MemberType)) &&
        IsSame<detail::WrapperMemberType<T>, MemberType>;
    
    /**
    * @brief Concept: Is Wrapper of Integer.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IntegerWrapper = 
        IsWrapperOf<T, short>     || IsWrapperOf<T, unsigned short> ||
        IsWrapperOf<T, int>       || IsWrapperOf<T, unsigned int>   ||
        IsWrapperOf<T, long>      || IsWrapperOf<T, unsigned long>  ||
        IsWrapperOf<T, long long> || IsWrapperOf<T, unsigned long long>;
    
    /**
    * @brief Using: Remove Reference.
    * 
    * @tparam T .
    */
    template<typename T>
    using RemoveRef = std::remove_reference_t<T>;
    
    /**
    * @brief Using: Decay.
    * 
    * @tparam T .
    */
    template<typename T>
    using Decay = std::decay_t<T>;
}