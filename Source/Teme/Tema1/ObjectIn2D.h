#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace ObjectIn2D
{

	// Create rectangle with given bottom left corner, length and color
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color, bool fill = false);
	Mesh* CreateCircle(std::string name, float radius, glm::vec3 color, float step, bool fill);
	Mesh* CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color, bool fill = false);

	Mesh* CreateSemicircle(std::string name, float radius, glm::vec3 color, float step);

}

