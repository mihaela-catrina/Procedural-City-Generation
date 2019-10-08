#pragma once

#include <include/glm.h>

namespace Tema2_3DTransform
{
	// Translate matrix
	inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
	{
		// TODO implement translate matrix
		return glm::transpose(
			glm::mat4(1, 0, 0, translateX,
				0, 1, 0, translateY,
				0, 0, 1, translateZ,
				0, 0, 0, 1)
		);
	}

	// Scale matrix
	inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
	{
		// TODO implement scale matrix
		return glm::transpose(
			glm::mat4(scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, scaleZ, 0,
				0, 0, 0, 1)
		);
	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(
			glm::mat4(std::cos(radians), (-1)*std::sin(radians), 0, 0,
				std::sin(radians), std::cos(radians), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1)
		);
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(
			glm::mat4(std::cos(radians), 0, std::sin(radians), 0,
				0, 1, 0, 0,
				(-1)*std::sin(radians), 0, std::cos(radians), 0,
				0, 0, 0, 1)
		);
	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(
			glm::mat4(1, 0, 0, 0,
				0, std::cos(radians), (-1)*std::sin(radians), 0,
				0, std::sin(radians), std::cos(radians), 0,
				0, 0, 0, 1)
		);
	}
}
