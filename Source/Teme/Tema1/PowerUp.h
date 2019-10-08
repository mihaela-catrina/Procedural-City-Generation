#include <iostream>
#include <Core/Engine.h>

class PowerUp {
protected:
	Mesh* mesh;

public:
	std::string name;
	float positionX;
	float positionY;
	int width;
	int height;
	float angle = 0;
	bool captured = false;
	PowerUp() {}
	PowerUp(std::string _name, int _width, int _height)
		: name(_name), positionX(0.0f), positionY(0.0f), width(_width), height(_height) {}
	PowerUp(std::string _name, float x, float y, int _width, int _height)
		: name(_name), positionX(x), positionY(y), width(_width), height(_height) {}

	void setMesh(Mesh *m)
	{
		mesh = m;
	}

	Mesh* getMesh()
	{
		return mesh;
	}

	// update powerUp state (position and rotation on canvas)
	void update(float deltaTime)
	{
		angle += 3 * deltaTime;
		positionY -= 100 * deltaTime;
	}
};