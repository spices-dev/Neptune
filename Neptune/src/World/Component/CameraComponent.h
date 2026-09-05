/**
* @file CameraComponent.h.
* @brief The CameraComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "GamePlay/Camera/Camera.h"

namespace Neptune {

    /**
    * @brief CameraComponent Class.
    * This class defines the specific behaves of CameraComponent.
    */
    class CameraComponent : public Component<SP<Camera>>
    {
    public:

        /**
        * @brief Constructor Function.
        */
        CameraComponent() = default;

        /**
        * @brief Constructor Function.
        * 
        * @param[in] camera Object.
        */
        CameraComponent(const SP<Camera>& camera) : Component(camera) {}

        /**
        * @brief Destructor Function.
        */
        ~CameraComponent() override = default;

    };
}