/**
* @file Transform.h.
* @brief The Transform Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Transform.h"

namespace Neptune {

    using namespace Data;

    glm::mat4 GetRotationMatrix(const glm::vec3& rotation)
    {
        NEPTUNE_PROFILE_ZONE

        return
        glm::toMat4(
            glm::quat({
                glm::radians(rotation.x),
                glm::radians(rotation.y),
                glm::radians(rotation.z)
            })
        );
    }

    glm::mat4 ToMatrix(const Transform& transform)
    {
        NEPTUNE_PROFILE_ZONE

        return
        glm::translate(glm::mat4(1.0f), transform.position) *
        GetRotationMatrix(transform.rotation) *
        glm::scale(glm::mat4(1.0f), transform.scale);
    }
}