/**
* @file Context.h.
* @brief The Context Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/KVTuple.h"
#include "Device/Graphics/Backend/Common/Concept.h"

namespace Neptune::Graphic::Common {
    
    /**
    * @brief Template of ContextElement Class Definitions.
    * 
    * @tparam T_ ContextElement Class.
    * @tparam E_ EExtension.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
    struct IContextElement : Container::KVTuple<T_, E_>
    {
        using KVTuple = Container::KVTuple<T_, E_>;
        
        using T = KVTuple::T;

        static constexpr auto E = KVTuple::E;
    };
    
    /**
    * @brief ContextElement Factory.
    *
    * @tparam Element ContextElement.
    * @tparam T Specification of ContextElement.
    * @param[in] c Context.
    * @param[in] e EElement.
    * @param[in] args ContextElement Params.
    * 
    * @return Returns ContextElement.
    */
    template<typename Element, typename T, typename C, typename E, typename... Args>
    requires IsContextElementBuildable<Element, T, C, E, Args...>
    static UP<T> ContextElementFactory(C& c, E e, Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsHasStaticFactory<T, C&, E, Args...>)
        {
            return T::Create(c, e, std::forward<Args>(args)...);
        }
        else if constexpr (IsHasStaticFactory<T, Args...>)
        {
            return T::Create(std::forward<Args>(args)...);
        }
        else if constexpr (IsConstructible<T, C&, E, Args...>)
        {
            return CreateUP<T>(c, e, std::forward<Args>(args)...);
        }
        else
        {
            return CreateUP<T>(std::forward<Args>(args)...);
        }
    }
    
    /**
    * @brief Context.
    * 
    * @tparam Element Element.
    * @tparam E EExtension.
    */
    template<typename Element, typename E>
    requires IsEnum<E>
    class Context final
    {
    public:
        
        NONE_COPY(Context)
        
        /**
        * @brief Constructor Function.
        */
        Context() = default;
        
        /**
        * @brief Destructor Function.
        */
        ~Context() = default;

        /**
        * @brief Registry IContextElement.
        *
        * @tparam I IContextElement Definitions.
        * @param[in] args IContextElement::T Construct Params.
        */
        template<typename I, typename... Args>
        requires IsIContextElement<Element, I> && 
                 IsNotEmptyEnum<E> &&
                 IsContextElementBuildable<Element, typename I::T, Context<Element, E>, decltype(I::E), Args...>
        typename I::T* Registry(Args&&... args);
        
        /**
        * @brief Unregister Infrastructure.
        *
        * @tparam I IContextElement Definitions
        * 
        * @return Returns true if succeeded.
        */
        template<typename I>
        requires IsIContextElement<Element, I> && 
                 IsNotEmptyEnum<E>
        bool UnRegistry();
        
        /**
        * @brief Unregister Infrastructure.
        *
        * @param[in] e E.
        * 
        * @return Returns true if succeeded.
        */
        bool UnRegistry(E e) requires IsNotEmptyEnum<E>;
        
        /**
        * @brief Unregister All Infrastructure.
        */
        void UnRegistry() requires IsNotEmptyEnum<E>;
        
        /**
        * @brief Get registry IContextElement.
        *
        * @tparam I IContextElement Definitions.
        * 
        * @return Returns registry IContextElement.
        */
        template<typename I>
        requires IsIContextElement<Element, I> && 
                 IsNotEmptyEnum<E>
        typename I::T* Get() const;
        
        /**
        * @brief Is registry IContextElement.
        *
        * @tparam I IContextElement Definitions.
        * 
        * @return Returns true if registry.
        */
        template<typename I>
        requires IsIContextElement<Element, I> && 
                 IsNotEmptyEnum<E>
        bool Has() const;
        
        /**
        * @brief View all Infrastructures.
        * 
        * @param[in] fn Iter Functor.
        */
        template<typename F>
        requires IsNotEmptyEnum<E>
        void View(F&& fn) const;
        
    private:

        MetaProperty(TEST)
        NO_UNIQUE_ADDRESS std::conditional_t<
            static_cast<uint8_t>(E::Count) == 0,
            std::monostate,
            std::array<UP<Element>, static_cast<uint8_t>(E::Count)>
        > m_Infrastructures;                   // @brief Container of EContext.

    };

    template<typename Element, typename E> requires IsEnum<E>
    template<typename I, typename... Args>
    requires IsIContextElement<Element, I> && 
             IsNotEmptyEnum<E> &&
             IsContextElementBuildable<Element, typename I::T, Context<Element, E>, decltype(I::E), Args...>
    inline typename I::T* Context<Element, E>::Registry(Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        m_Infrastructures[position] = ContextElementFactory<Element, typename I::T>(*this, I::E, std::forward<Args>(args)...);
        
        return Get<I>();
    }

    template <typename Element, typename E> requires IsEnum<E>
    template <typename I> 
    requires IsIContextElement<Element, I> && 
             IsNotEmptyEnum<E>
    inline bool Context<Element, E>::UnRegistry()
    {
        NEPTUNE_PROFILE_ZONE

        return UnRegistry(I::E);
    }

    template<typename Element, typename E> requires IsEnum<E>
    inline bool Context<Element, E>::UnRegistry(E e) requires IsNotEmptyEnum<E>
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(e);

        if (!m_Infrastructures[position]) return false;

        m_Infrastructures[position].reset();
        
        return true;
    }

    template <typename Element, typename E> requires IsEnum<E>
    inline void Context<Element, E>::UnRegistry() requires IsNotEmptyEnum<E>
    {
        NEPTUNE_PROFILE_ZONE

        for (int i = static_cast<int>(E::Count) - 1; i >= 0; --i)
        {
            UnRegistry(static_cast<E>(i));
        }
    }

    template<typename Element, typename E> requires IsEnum<E>
    template<typename I>
    requires IsIContextElement<Element, I> && 
             IsNotEmptyEnum<E>
    typename I::T* Context<Element, E>::Get() const
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        return static_cast<I::T*>(m_Infrastructures[position].get());
    }
    
    template<typename Element, typename E> requires IsEnum<E>
    template<typename I>
    requires IsIContextElement<Element, I> && 
             IsNotEmptyEnum<E>
    bool Context<Element, E>::Has() const
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }
    
    template<typename Element, typename E> requires IsEnum<E>
    template<typename F>
    requires IsNotEmptyEnum<E>
    void Context<Element, E>::View(F&& fn) const
    {
        NEPTUNE_PROFILE_ZONE
        
        for (uint8_t i = 0; i < static_cast<uint8_t>(E::Count); ++i)
        {
            if (!m_Infrastructures[i]) continue;
            
            std::invoke(std::forward<F>(fn), static_cast<E>(i), m_Infrastructures[i].get());
        }
    }
}
