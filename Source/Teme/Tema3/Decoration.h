#include "Objects.h"

class Decoration {
public:
	Mesh* mesh;
	std::string texture;
	float x1;
	float x2;
	float z1;
	float z2;

public:
	Decoration(Mesh* mesh, std::string texture, float x1, float x2, float z1, float z2) : 
		mesh(mesh), texture(texture), x1(x1), x2(x2), z1(z1), z2(z2) {};
};