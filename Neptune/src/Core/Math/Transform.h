/**
* @file Transform.h.
* @brief The Transform Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Data/Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Neptune {
    
    /**
    * @brief Get Rotation Matrix.
    * 
    * @param[in] rotation Rotation Component.
    * 
    * @return Returns Rotation Matrix.
    */
    glm::mat4 GetRotationMatrix(const glm::vec3& rotation);

    /**
    * @brief Get Model Matrix from specific Transform.
    * 
    * @param[in] transform Specific transform.
    * 
    * @reutrn Returns specific transform Matrix.
    */
    glm::mat4 ToMatrix(const Data::Transform& transform);
}