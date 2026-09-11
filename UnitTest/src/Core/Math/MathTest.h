/**
* @file MathTest.h.
* @brief The MathTest Definitions.
* @author Spices.
*/

#pragma once
#include "Instrumentor.h"

#include <Core/Math/Math.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <gmock/gmock.h>

namespace Neptune {

	/**
	* @brief Testing DecomposeTransform.
	*/
	TEST(MathTest, DecomposeTransform) {

		NEPTUNE_TEST_PROFILE_FUNCTION

		{
			glm::mat4 matrix = {
				-1, 0,  0, 0,
				 0, 1,  0, 0,
				 0, 0, -1, 0,
				 0, 0,  0, 1
			};
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;

			EXPECT_TRUE(DecomposeTransform(matrix, position, rotation, scale));

			rotation = glm::vec3(glm::degrees(rotation.x), glm::degrees(rotation.y), glm::degrees(rotation.z));
		}

		{
			glm::mat4 matrix = {
				1, 0, 0, 0, 
				0, 1, 0, 0, 
				0, 0, 1, 0, 
				0, 0, 0, 1
			};
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;

			EXPECT_TRUE(DecomposeTransform(matrix, position, rotation, scale));

			rotation = glm::vec3(glm::degrees(rotation.x), glm::degrees(rotation.y), glm::degrees(rotation.z));
		}

		{
			glm::quat rotationQuat = glm::quat(0.5f, -0.5f, -0.5f, -0.5f);
			glm::mat4 matrix = glm::toMat4(rotationQuat);

			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;

			EXPECT_TRUE(DecomposeTransform(matrix, position, rotation, scale));

			rotation = glm::vec3(glm::degrees(rotation.x), glm::degrees(rotation.y), glm::degrees(rotation.z));
		}

		{
			glm::quat rotationQuat({ -0.7898206f, 0.613338f, 0.0f, 0.0f });
			glm::mat4 matrix = glm::toMat4(rotationQuat);

			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;

			EXPECT_TRUE(DecomposeTransform(matrix, position, rotation, scale));

			rotation = glm::vec3(glm::degrees(rotation.x), glm::degrees(rotation.y), glm::degrees(rotation.z));
		}
	}
}
