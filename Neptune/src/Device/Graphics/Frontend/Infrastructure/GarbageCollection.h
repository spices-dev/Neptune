/**
* @file GarbageCollection.h.
* @brief The GarbageCollection Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Concept.h"
#include "Render/Frontend/Core.h"

namespace Neptune::Graphic {

    /**
    * @brief Graphic::GarbageCollection Class.
    * This class defines the Graphic::GarbageCollection behaves.
    */
    class GarbageCollection
    {
    public:

        /**
        * @brief Constructor Function.
        */
        GarbageCollection() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~GarbageCollection();
		
        /**
        * @brief Set Frame id.
        * 
        * @param[in] frameId Frame id.
        */
        void SetFrameId(uint64_t frameId) { m_Id = frameId; }
        
        /**
        * @brief Free Garbage.
        * 
        * @param[in] frameId Frame id.
        */
        void Flush(uint64_t frameId);
        
        /**
        * @brief Free Garbage.
        */
        void Flush();
        
        /**
        * @brief Retire object.
        * 
        * @param[in] object .
        */
        template<typename T>
        void Retire(T&& object);
        
    private:
        
        /**
        * @brief Interface of Garbage.
        */
        struct IGarbage { virtual ~IGarbage() = default; };
        
        /**
        * @brief Object Garbage.
        * 
        * @tparam T
        */
        template<typename T>
        struct Object final : IGarbage
        {
            /**
            * @brief Constructor Function.
            * 
            * @param[in] t T
            */
            explicit Object(T&& t) : m_Object(std::move(t)) {}
            
            T m_Object;  // @brief Object.
        };
        
        /**
        * @brief Function Garbage.
        * 
        * @tparam T
        */
        template<IsInvocable T>
        struct Function final : IGarbage
        {
            /**
            * @brief Constructor Function.
            * 
            * @param[in] t T
            */
            explicit Function(T&& t) : m_Function(std::move(t)) {}
            
            /**
            * @brief Destructor Function.
            */
            ~Function() override { std::invoke(m_Function); }
            
            T m_Function;  // @brief Function.
        };
        
        std::array<std::vector<UP<IGarbage>>, MaxFrameInFlight> m_Buckets;   // @brief Garbage Buckets.
        uint64_t m_Id = 0;                                                   // @brief Frame id.
        std::mutex m_Mutex;                                                  // @brief This mutex.
    };

    template <typename T>
    void GarbageCollection::Retire(T&& object)
    {
        NEPTUNE_PROFILE_ZONE
        
        using Type = Decay<T>;
        
        static_assert(IsMoveConstructible<Type>);
        
        UP<IGarbage> entry;

        if constexpr (IsInvocable<Type>)
        {
            entry = CreateUP<Function<Type>>(std::forward<T>(object));
        }
        else
        {
            entry = CreateUP<Object<Type>>(std::forward<T>(object));
        }
        
        std::unique_lock lock(m_Mutex);
        
        m_Buckets[m_Id % MaxFrameInFlight].emplace_back(std::move(entry));
    }
}