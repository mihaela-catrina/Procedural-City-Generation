#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects
{

	// Create rectangle with given bottom left corner, length and color
	Mesh* CreateRectangle(std::string name, glm::vec3 center, float sizeX, float sizeY, glm::vec2 textCoord);
	std::pair<Mesh*, Mesh*> CreateBuilding(std::string name, float _radius, glm::vec3 center, int faces, float height);
}

