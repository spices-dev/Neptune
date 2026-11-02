/**
* @file Unit.h.
* @brief The Unit Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::Vulkan::Unit {

    /**
    * @brief LifeDelegate.
    * 
    * @tparam C Construct Function.
    * @tparam D Destruct Function.
    */
    template<typename C, typename D>
    struct LifeDelegate
    {
        C                            constructor = nullptr;
        D                            destructor  = nullptr;
        const VkAllocationCallbacks* allocator   = nullptr;
    };
    
    /**
    * @brief Common::Unit Class.
    * This class defines the Common::Unit behaves.
    * 
    * @tparam H Handle.
    * @tparam C Construct Function.
    * @tparam D Destruct Function.
    */
    template<typename H, typename C, typename D>
    class Unit
    {
    public:

        using Handle       = H;
        using LifeDelegate = LifeDelegate<C, D>;

        NONE_COPY(Unit)
		
    public:

        /**
        * @brief Constructor Function.
        */
        Unit() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~Unit() { ResetHandle(); }

        /**
        * @brief Move Constructor Function.
        *
        * @param[in] other Unit.
        */
        Unit(Unit&& other) noexcept
        {
            SetHandle(other.GetHandle());
			
            other.ResetHandle();
        }

        /**
        * @brief Move Assignment Operation.
        *
        * @param[in] other Unit.
        * 
        * @return Returns this.
        */
        Unit& operator=(Unit&& other) noexcept
        {
            SetHandle(other.GetHandle());
			
            other.ResetHandle();
			
            return *this;
        }

        /**
        * @brief Set Unit Handle.
        *
        * @param[in] handle Unit Handle.
        */
        void SetHandle(const Handle& handle) { m_Handle = handle; }

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Handle& GetHandle() const { return m_Handle; }

        /**
        * @brief Reset Unit Handle.
        */
        void ResetHandle() { m_Handle = {}; }

        /**
        * @brief Set Life.
        * 
        * @param[in] life LifeDelegate.
        */
        void SetLife(const LifeDelegate& life) { m_Life = life; }
        
    protected:

        Handle       m_Handle{};      // @brief Unit Handle.
        LifeDelegate m_Life{};        // @brief Unit Life Delegate.
    };
}