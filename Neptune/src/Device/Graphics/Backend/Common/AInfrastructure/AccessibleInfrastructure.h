/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/Tuple.h"
#include "Device/Graphics/Backend/Common/Context/Context.h"

namespace Neptune::Graphic::Common {

    /**
    * @brief Template of Accessible Infrastructure Class Definitions.
    * 
    * @tparam T_ AccessibleInfrastructure Class.
    * @tparam E_ EAccessibleInfrastructure.
    */
    template<typename T_, auto E_>
    requires IsEnum<decltype(E_)>
    using AccessibleInfrastructure = Graphic::Common::IContextElement<T_, E_>;
    
    /**
    * @brief RenderBackend AccessibleContext.
    * 
    * @tparam E EAccessibleInfrastructure.
    * @tparam T AccessibleInfrastructureTuple.
    */
    template<IsEnum E, IsTuple T>
    class AccessibleContext final
    {
    public:
        
        using AInfrastructures = Container::wrap_tuple_t<std::optional, T>;
        
    public:
        
        /**
        * @brief Constructor Function.
        */
        AccessibleContext() = default;

        /**
        * @brief Constructor Function.
        * 
        * @param[in] infrastructures AccessibleInfrastructures.
        */
        AccessibleContext(const AInfrastructures& infrastructures)
            : m_Infrastructures(infrastructures)
        {}
        
        /**
        * @brief Destructor Function.
        */
        ~AccessibleContext() = default;

        /**
        * @brief Registry AccessibleInfrastructure.
        *
        * @tparam A AccessibleInfrastructure Definitions.
        * @param[in] t AccessibleInfrastructure::T.
        */
        template<IsAInfrastructure A>
        requires IsNotEmptyEnum<E>
        void Registry(const typename A::T& t);

        /**
        * @brief Get registry AccessibleInfrastructure.
        *
        * @tparam A AccessibleInfrastructure Definitions.
        * 
        * @return Returns registry AccessibleInfrastructure.
        */
        template<IsAInfrastructure A>
        requires IsNotEmptyEnum<E>
        typename A::T Get();

        /**
        * @brief Is AccessibleInfrastructure registry.
        *
        * @tparam A AccessibleInfrastructure Definitions.
        * 
        * @return Returns true if registry.
        */
        template<IsAInfrastructure A>
        requires IsNotEmptyEnum<E>
        bool Has();
        
    private:

        MetaProperty(TEST)
        NO_UNIQUE_ADDRESS std::conditional_t<
            static_cast<uint8_t>(E::Count) == 0,
            std::monostate,
            AInfrastructures
        > m_Infrastructures;                   // @brief Container of AccessibleInfrastructure.

    };

    template<IsEnum E, IsTuple T>
    template<IsAInfrastructure A>
    requires IsNotEmptyEnum<E>
    inline void AccessibleContext<E, T>::Registry(const typename A::T& t)
    {
        constexpr auto position = static_cast<uint8_t>(A::E);

        std::get<position>(m_Infrastructures) = { t };
    }

    template<IsEnum E, IsTuple T>
    template<IsAInfrastructure A>
    requires IsNotEmptyEnum<E>
    typename A::T AccessibleContext<E, T>::Get()
    {
        constexpr auto position = static_cast<uint8_t>(A::E);

        return std::get<position>(m_Infrastructures).value();
    }
    
    template <IsEnum E, IsTuple T>
    template <IsAInfrastructure A> requires IsNotEmptyEnum<E>
    bool AccessibleContext<E, T>::Has()
    {
        constexpr auto position = static_cast<uint8_t>(A::E);
        
        return std::get<position>(m_Infrastructures).has_value();
    }
}
