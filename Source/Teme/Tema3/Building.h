#include "Objects.h"
class Building {
public:
	std::pair<Mesh*, Mesh*> buildingBase;
	float baseHeight;
	std::vector< std::pair<Mesh*, Mesh*>> floors;
	int floorNo = 0;
	glm::vec3 center;
public:
	Building(std::pair<Mesh*, Mesh*> base, float h, glm::vec3 center) : buildingBase(base), baseHeight(h), center(center) {}
};