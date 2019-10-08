#include <iostream>
#include <Core/Engine.h>

class Wall {
public:
	std::string name;
	float positionX;
	float positionY;
	int width;
	int height;
	static const int wallSize = 15;

	Wall(std::string _name, int _width, int _height) 
		: name(_name), positionX(0.0f), positionY(0.0f), width(_width), height(_height) {}
	Wall(std::string _name, float x, float y, int _width, int _height) 
		: name(_name), positionX(x), positionY(y), width(_width), height(_height) {}
};