/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Device/Graphics/Frontend/Core.h"
#include "Device/Graphics/Backend/Common/Context/Context.h"
#include "Core/Container/KVTuple.h"

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
    * @brief Link Mergeable type info(address).
    * 
    * @tparam A AInfrastructure.
    */
    template<IsAInfrastructure A>
    struct MergeableTypeInfo
    {
        typename A::T Value;
    };
    
    /**
    * @brief RenderBackend AccessibleContext.
    * 
    * @tparam E EAccessibleInfrastructure.
    */
    template<typename E>
    requires IsEnum<E>
    class AccessibleContext final
    {
    public:
        
        /**
        * @brief Constructor Function.
        */
        AccessibleContext()
        {
            if constexpr (static_cast<uint8_t>(E::Count) != 0)
            {
                m_Infrastructures = std::vector<std::any>(static_cast<uint8_t>(E::Count));
            }
        }

        /**
        * @brief Constructor Function.
        * 
        * @param[in] infrastructures AccessibleInfrastructures.
        */
        AccessibleContext(const AInfrastructures& infrastructures)
            : m_Infrastructures(infrastructures)
        {
            assert(infrastructures.size() == static_cast<uint8_t>(E::Count));
        }
        
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
        * @brief Get All AccessibleInfrastructure.
        * 
        * @return Returns All AccessibleInfrastructure.
        */
        const AInfrastructures& GetInfrastructures() const
        {
            NEPTUNE_PROFILE_ZONE

            static AInfrastructures null = {};

            if constexpr (static_cast<uint8_t>(E::Count) == 0)
            {
                return null;
            }
            else
            {
                return m_Infrastructures;
            }
        }
        
    private:

        MetaProperty(TEST)
        NO_UNIQUE_ADDRESS std::conditional_t<
            static_cast<uint8_t>(E::Count) == 0,
            std::monostate,
            AInfrastructures
        > m_Infrastructures;                   // @brief Container of AccessibleInfrastructure.

    };

    template<typename E> requires IsEnum<E>
    template<IsAInfrastructure A>
    requires IsNotEmptyEnum<E>
    inline void AccessibleContext<E>::Registry(const typename A::T& t)
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(A::E);

        m_Infrastructures[position] = MergeableTypeInfo<A> { t };
    }

    template<typename E> requires IsEnum<E>
    template<IsAInfrastructure A>
    requires IsNotEmptyEnum<E>
    typename A::T AccessibleContext<E>::Get()
    {
        NEPTUNE_PROFILE_ZONE

        const auto position = static_cast<uint8_t>(A::E);

        return std::any_cast<const MergeableTypeInfo<A>&>(m_Infrastructures.at(position)).Value;
    }
    
}
