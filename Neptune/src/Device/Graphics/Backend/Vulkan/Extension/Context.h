/**
* @file Context.h.
* @brief The Context Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Extension.h"
#include "Concept.h"
#include "Enum.h"

namespace Neptune::Vulkan::Extension {
    
    /**
    * @brief Template of Extension Class Definitions.
    * 
    * @tparam T_ Extension Class.
    * @tparam E_ EExtension.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
    struct IExtension : Container::KVTuple<T_, E_>
    {
        using KVTuple = Container::KVTuple<T_, E_>;
        
        using T = KVTuple::T;

        static constexpr auto E = KVTuple::E;
    };
    
    /**
    * @brief Extension Context.
    * 
    * @tparam E EExtension.
    */
    template<typename E>
    requires IsEnum<E>
    class EContext final
    {
    public:
        
        /**
        * @brief Constructor Function.
        */
        EContext() = default;
        
        /**
        * @brief Destructor Function.
        */
        ~EContext() = default;

        /**
        * @brief Registry IExtension.
        *
        * @tparam I IExtension Definitions.
        * @param[in] args IExtension::T Construct Params.
        */
        template<IsIExtension I, typename... Args>
        requires IsNotEmptyEnum<E>
        void Registry(Args&&... args);

        /**
        * @brief Unregister Infrastructure.
        *
        * @param[in] e E.
        */
        void UnRegistry(E e);
        
        /**
        * @brief Get registry IExtension.
        *
        * @tparam I IExtension Definitions.
        * 
        * @return Returns registry IExtension.
        */
        template<IsIExtension I>
        requires IsNotEmptyEnum<E>
        typename I::T* Get() const;
        
        /**
        * @brief Is registry IExtension.
        *
        * @tparam I IExtension Definitions.
        * 
        * @return Returns true if registry.
        */
        template<IsIExtension I>
        requires IsNotEmptyEnum<E>
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
            std::array<UP<Extension>, static_cast<uint8_t>(E::Count)>
        > m_Infrastructures;                   // @brief Container of EContext.

    };

    template<typename E> requires IsEnum<E>
    template<IsIExtension I, typename... Args>
    requires IsNotEmptyEnum<E>
    inline void EContext<E>::Registry(Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        m_Infrastructures[position] = CreateUP<typename I::T>(std::forward<Args>(args)...);
    }

    template<typename E> requires IsEnum<E>
    inline void EContext<E>::UnRegistry(E e)
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(e);

        if (!m_Infrastructures[position]) return;

        m_Infrastructures[position].reset();
    }
    
    template<typename E> requires IsEnum<E>
    template<IsIExtension I>
    requires IsNotEmptyEnum<E>
    typename I::T* EContext<E>::Get() const
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        return static_cast<I::T*>(m_Infrastructures[position].get());
    }
    
    template<typename E> requires IsEnum<E>
    template<IsIExtension I>
    requires IsNotEmptyEnum<E>
    bool EContext<E>::Has() const
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }
    
    template<typename E> requires IsEnum<E>
    template<typename F>
    requires IsNotEmptyEnum<E>
    void EContext<E>::View(F&& fn) const
    {
        NEPTUNE_PROFILE_ZONE
        
        for (uint8_t i = 0; i < static_cast<uint8_t>(E::Count); ++i)
        {
            std::invoke(std::forward<F>(fn), static_cast<E>(i), m_Infrastructures[i].get());
        }
    }
}

#endif