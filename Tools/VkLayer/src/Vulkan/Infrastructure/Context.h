/**
* @file Context.h.
* @brief The Context Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <array>

namespace Neptune::Vulkan {
    
    /**
    * @brief Template of ContextElement Class Definitions.
    * 
    * @tparam T_ ContextElement Class.
    * @tparam E_ EExtension.
    */
    template<typename T_, auto E_>
    struct IInfrastructure
    {
        using T = T_;

        static constexpr auto E = E_;
    };
    
    /**
    * @brief Context.
    * 
    * @tparam Element Element.
    * @tparam E EExtension.
    */
    template<typename Element, typename E>
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
        typename I::T* Registry(Args&&... args);
        
        /**
        * @brief Unregister Infrastructure.
        *
        * @tparam I IContextElement Definitions
        * 
        * @return Returns true if succeeded.
        */
        template<typename I>
        bool UnRegistry();
        
        /**
        * @brief Unregister All Infrastructure.
        */
        void UnRegistry();
        
        /**
        * @brief Get registry IContextElement.
        *
        * @tparam I IContextElement Definitions.
        * 
        * @return Returns registry IContextElement.
        */
        template<typename I>
        typename I::T* Get() const;
        
        /**
        * @brief Is registry IContextElement.
        *
        * @tparam I IContextElement Definitions.
        * 
        * @return Returns true if registry.
        */
        template<typename I>
        bool Has() const;
        
    private:
        
        std::array<UP<Element>, static_cast<uint8_t>(E::Count)> m_Infrastructures; // @brief Container of EContext.
    };

    template<typename Element, typename E>
    template<typename I, typename... Args>
    inline typename I::T* Context<Element, E>::Registry(Args&&... args)
    {
        constexpr auto position = static_cast<uint8_t>(I::E);

        m_Infrastructures[position] = CreateUP<typename I::T>(std::forward<Args>(args)...);
        
        return Get<I>();
    }

    template <typename Element, typename E>
    template <typename I> 
    inline bool Context<Element, E>::UnRegistry()
    {
        constexpr auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position]) return false;

        m_Infrastructures[position].reset();

        return true;
    }

    template <typename Element, typename E>
    inline void Context<Element, E>::UnRegistry()
    {
        for (int i = static_cast<int>(E::Count) - 1; i >= 0; --i)
        {
            UnRegistry(static_cast<E>(i));
        }
    }

    template<typename Element, typename E>
    template<typename I>
    typename I::T* Context<Element, E>::Get() const
    {
        constexpr auto position = static_cast<uint8_t>(I::E);

        return static_cast<typename I::T*>(m_Infrastructures[position].get());
    }

    template<typename Element, typename E>
    template<typename I>
    bool Context<Element, E>::Has() const
    {
        constexpr auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }
}
