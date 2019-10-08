#include <iostream>
#include <Core/Engine.h>

class Ball {

public:
	std::string name;
	float positionX;
	float positionY;
	int radius;
	int directionX;             //+1/-1 -> right/left
	int directionY;             //+1/-1 -> up/down
	float angle;
	bool isOnScene = true;      // true is the ball didn't exceed the scene resolution
	bool strengthOn = false;    // true when a NO_REFLECTION powerUp is captured

	Ball() {};
	Ball(const Ball&) = default;
	Ball(std::string _name, int _radius)
		: name(_name), positionX(0.0f), positionY(0.0f), radius(_radius) {}
	Ball(std::string _name, float x, float y, int _radius)
		: name(_name), positionX(x), positionY(y), radius(_radius) {}

	Ball& operator=(const Ball&) = default;
};