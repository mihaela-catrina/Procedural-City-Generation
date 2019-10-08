#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include <Core/Engine.h>

namespace Transformations {
	// Translate matrix
	inline glm::mat3 Translate(float tx, float ty)
	{
		return glm::transpose(
			glm::mat3(1, 0, tx,
				0, 1, ty,
				0, 0, 1)
		);
	}


	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		// implement scale matrix
		return glm::mat3(scaleX, 0, 0,
			0, scaleY, 0,
			0, 0, 1);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		// implement rotate matrix
		return glm::mat3(std::cos(radians), (-1) * std::sin(radians), 0,
			std::sin(radians), std::cos(radians), 0,
			0, 0, 1);
	}
}