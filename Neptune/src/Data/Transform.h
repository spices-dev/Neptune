/**
* @file Transform.h.
* @brief The Transform Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <glm/vec3.hpp>

namespace Neptune::Data {

    /**
    * @brief 3D Transform
    */
    struct Transform
    {
        glm::vec3 position{ 0.0f };         /* @brief Position Component. */
        glm::vec3 rotation{ 0.0f };         /* @brief Rotation Component. */
        glm::vec3 scale   { 1.0f };         /* @brief Scale    Component. */
    };
}