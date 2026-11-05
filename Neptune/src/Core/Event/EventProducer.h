/**
* @file EventProducer.h.
* @brief The EventProducer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"

namespace Neptune {
    
    /**
    * @brief The EventProducer Class.
    */
    class EventProducer
    {
    public:

        /**
        * @brief Constructor Function.
        */
        EventProducer() = default;
    
        /**
        * @brief Constructor Function.
        *
        * @param[in] bit EventType.
        */
        explicit EventProducer(EventType bit)
        {
            Registry(bit);
        }
        
        /**
        * @brief Destructor Function.
        */
        virtual ~EventProducer() = default;
        
        /**
        * @brief Registry interested event type.
        * 
        * @param[in] bit EventType.
        */
        void Registry(EventType bit)
        {
            m_Interested.Set(bit, true);
        }
        
        /**
        * @brief UnRegistry interested event type.
        * 
        * @param[in] bit EventType.
        */
        void UnRegistry(EventType bit)
        {
            m_Interested.Set(bit, false);
        }
        
        /**
        * @brief Dispatch interested event.
        * 
        * @param[in] event Event
        */
        void Dispatch(Event& event) const
        {
            NEPTUNE_PROFILE_ZONE

            if(!m_Interested.Test(event.GetEventType())) 
            {
                return;
            }

            DispatchEvent(event);
        }
        
    private:
        
        /**
        * @brief Dispatch Event to Listener.
        * 
        * @param[in] event Event
        */
        void DispatchEvent(Event& event) const
        {
            NEPTUNE_PROFILE_ZONE
            
            Event::GetEventCallbackFn()(event);
        }
        
    private:

        /**
        * @brief Interested event type.
        */
        Container::BitSet<EventType> m_Interested{};
        
    };
    

}