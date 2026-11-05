/**
* @file KeyEvent.h.
* @brief The KeyEvent Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"
#include "Core/Input/KeyCodes.h"

namespace Neptune {

    /**
    * @brief This Class is inherited from Event Class.
    * Inherit from it and create specific KeyEvent class.
    */
    class KeyEvent : public Event
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~KeyEvent() override = default;

        /**
        * @brief Get Key Input Code.
        * 
        * @return Returns the Key Input Code.
        */
        [[nodiscard]] const KeyCode& GetKeyCode() const { return m_KeyCode; }

        /**
        * @brief Specific this Class Category with EventCategoryKeyboard and EventCategoryInput.
        */
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard, EventCategoryInput)

    protected:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] keycode Input KeyCode.
        */
        explicit KeyEvent(KeyCode keycode)
            : m_KeyCode(keycode)
        {}

    private:
        
        /**
        * @brief Input KeyCode.
        */
        KeyCode m_KeyCode;
    };

    /**
    * @brief This Class is inherited from KeyEvent Class.
    */
    class KeyPressedEvent : public KeyEvent
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] keycode Input KeyCode.
        * @param[in] repeatCount Input Key repeat count.
        */
        explicit KeyPressedEvent(KeyCode keycode, int repeatCount)
            : KeyEvent(keycode)
            , m_RepeatCount(repeatCount)
        {}

        /**
        * @brief Destructor Function.
        */
        virtual ~KeyPressedEvent() override = default;

        /**
        * @brief Get Input Key repeat count.
        * 
        * @return Returns the Input Key repeat count.
        */
        const int& GetRepeatCount() const { return m_RepeatCount; }

        /**
        * @brief Serialize this Event Class to string.
        * 
        * @return Returns Serialized string.
        */
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << Key::ToString(GetKeyCode()) << " (" << m_RepeatCount << " repeats)";

            return ss.str();
        }

        /**
        * @brief Specific this Class Type with KeyPressed.
        */
        EVENT_CLASS_TYPE(KeyPressed)

    private:

        /**
        * @brief The key repeat count.
        */
        int m_RepeatCount;
    };

    /**
    * @brief This Class is inherited from KeyEvent Class.
    */
    class KeyReleasedEvent : public KeyEvent
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] keycode Input KeyCode.
        */
        explicit KeyReleasedEvent(KeyCode keycode)
            : KeyEvent(keycode)
        {}

        /**
        * @brief Destructor Function.
        */
        ~KeyReleasedEvent() override = default;

        /**
        * @brief Serialize this Event Class to string.
        * 
        * @return Returns Serialized string.
        */
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << Key::ToString(GetKeyCode());

            return ss.str();
        }

        /**
        * @brief Specific this Class Type with KeyReleased.
        */
        EVENT_CLASS_TYPE(KeyReleased)
    };

    /**
    * @brief This Class is inherited from KeyEvent Class.
    */
    class KeyTypedEvent : public KeyEvent
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] keycode Input KeyCode.
        */
        explicit KeyTypedEvent(KeyCode keycode)
            : KeyEvent(keycode)
        {}

        /**
        * @brief Destructor Function.
        */
        ~KeyTypedEvent() override = default;

        /**
        * @brief Serialize this Event Class to string.
        * 
        * @return Returns Serialized string.
        */
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << Key::ToString(GetKeyCode());

            return ss.str();
        }

        /**
        * @brief Specific this Class Type with KeyTyped.
        */
        EVENT_CLASS_TYPE(KeyTyped)
    };
}