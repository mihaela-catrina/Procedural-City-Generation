#include <iostream>
#include <Core/Engine.h>

class Platform {
protected:
	Mesh* mesh;

public:
	std::string name;
	float positionX;
	float positionY;
	int width;
	int height;

	Platform() {};
	Platform(std::string _name, int _width, int _height)
		: name(_name), positionX(0.0f), positionY(0.0f), width(_width), height(_height) {}
	Platform(std::string _name, float x, float y, int _width, int _height)
		: name(_name), positionX(x), positionY(y), width(_width), height(_height) {}

	void setMesh(Mesh *m)
	{
		mesh = m;
	}
};