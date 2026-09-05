/**
* @file SOPComponent.h.
* @brief The SOPComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Asset/SOP/Object.h"

namespace Neptune {

    /**
    * @brief SOPComponent Class.
    * This class defines the specific behaves of SOPComponent.
    */
    class SOPComponent : public Component<SP<SOP::Object>>
    {
    public:

        /**
        * @brief Constructor Function.
        */
        SOPComponent() = default;

        /**
        * @brief Constructor Function.
        * 
        * @param[in] obj SOP::Object.
        */
        SOPComponent(const SP<SOP::Object>& obj) : Component(obj) {}

        /**
        * @brief Destructor Function.
        */
        ~SOPComponent() override = default;

        /**
        * @brief Rename first element in tags.
        * 
        * @param[in] tag new name.
        */
        void Rename(const std::string& tag);

    };
}