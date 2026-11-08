/**
* @file Context.h.
* @brief The Context Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Vulkan/Concept.h"

#include <array>

namespace Neptune::Vulkan {
    
    /**
    * @brief Template of Infrastructure Class Definitions.
    * 
    * @tparam T_ Infrastructure Class.
    * @tparam E_ EInfrastructure.
    */
    template<typename T_, auto E_>
    requires(IsEInfrastructure<Decay<decltype(E_)>>)
    struct IInfrastructure
    {
        using T = T_;

        static constexpr auto E = E_;
    };
    
    /**
    * @brief Context.
    * 
    * @tparam Element Element.
    * @tparam E EInfrastructure.
    */
    template<typename Element, IsEInfrastructure E>
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
        * @tparam I IInfrastructure Definitions.
        * @param[in] args IContextElement::T Construct Params.
        */
        template<IsIInfrastructure I, typename... Args>
        typename I::T* Registry(Args&&... args);
        
        /**
        * @brief Unregister Infrastructure.
        *
        * @tparam I IInfrastructure Definitions
        * 
        * @return Returns true if succeeded.
        */
        template<IsIInfrastructure I>
        bool UnRegistry();
        
        /**
        * @brief Get registry IInfrastructure.
        *
        * @tparam I IInfrastructure Definitions.
        * 
        * @return Returns registry IInfrastructure.
        */
        template<IsIInfrastructure I>
        typename I::T* Get() const;
        
        /**
        * @brief Is registry IInfrastructure.
        *
        * @tparam I IInfrastructure Definitions.
        * 
        * @return Returns true if registry.
        */
        template<IsIInfrastructure I>
        bool Has() const;
        
    private:
        
        std::array<UP<Element>, static_cast<uint8_t>(E::Count)> m_Infrastructures; // @brief Container of EContext.
    };

    template<typename Element, IsEInfrastructure E>
    template<IsIInfrastructure I, typename... Args>
    inline typename I::T* Context<Element, E>::Registry(Args&&... args)
    {
        constexpr auto position = static_cast<uint8_t>(I::E);

        m_Infrastructures[position] = CreateUP<typename I::T>(std::forward<Args>(args)...);
        
        return Get<I>();
    }

    template <typename Element, IsEInfrastructure E>
    template <IsIInfrastructure I> 
    inline bool Context<Element, E>::UnRegistry()
    {
        constexpr auto position = static_cast<uint8_t>(I::E);

        if (!m_Infrastructures[position]) return false;

        m_Infrastructures[position].reset();

        return true;
    }

    template<typename Element, IsEInfrastructure E>
    template<IsIInfrastructure I>
    typename I::T* Context<Element, E>::Get() const
    {
        constexpr auto position = static_cast<uint8_t>(I::E);

        return static_cast<typename I::T*>(m_Infrastructures[position].get());
    }

    template<typename Element, IsEInfrastructure E>
    template<IsIInfrastructure I>
    bool Context<Element, E>::Has() const
    {
        constexpr auto position = static_cast<uint8_t>(I::E);

        return m_Infrastructures[position] != nullptr;
    }
}
