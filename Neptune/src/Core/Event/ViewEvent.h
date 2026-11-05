/**
* @file ViewEvent.h.
* @brief The ViewEvent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Event.h"

#include <sstream>

namespace Neptune {

    /**
    * @brief This Class is inherited from Event Class.
    * Called by View Resize.
    */
    class ViewResizeEvent : public Event
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] width New View Size.
        * @param[in] height New View Size.
        */
        ViewResizeEvent(uint32_t width, uint32_t height)
            : m_Width(width)
            , m_Height(height)
        {}

        /**
        * @brief Destructor Function.
        */
        ~ViewResizeEvent() override = default;

        /**
        * @brief Get New View Width.
        * 
        * @return Returns the New View Width.
        */
        [[nodiscard]] const uint32_t& GetWidth() const { return m_Width; }

        /**
        * @brief Get New View Height.
        * 
        * @return Returns the New View Width.
        */
        [[nodiscard]] const uint32_t& GetHeight() const { return m_Height; }

        /**
        * @brief Serialize this Event Class to string.
        * 
        * @return Returns Serialized string.
        */
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "ViewResizeEvent: " << m_Width << ", " << m_Height;

            return ss.str();
        }

        /**
        * @brief Specific this Class Type with ViewResize.
        */
        EVENT_CLASS_TYPE(ViewResize)

        /**
        * @brief Specific this Class Category with EventCategoryView.
        */
        EVENT_CLASS_CATEGORY(EventCategoryView)

    private:

        /**
        * @brief New View Width.
        */
        uint32_t m_Width;

        /**
        * @brief New View Height.
        */
        uint32_t m_Height;
    };
}