#include <iostream>
#include <Core/Engine.h>
#include "PowerUp.h"
#include "ObjectIn2D.h"

enum BrickState {
	IDLE,
	CRUSHED,
	HIT,
	POWER_UP
};

enum PowerUpType {
	NOT_SETTED,
	WEAPON,
	NO_REFLECTION_ON_BRICK_COLLISION
};

class Brick {
protected:
	static const int powerUpWidth = 10;
	static const int powerUpHeight = 10;

public:
	std::string name;
	float positionX;
	float positionY;
	int width;
	int height;
	float scaleFactorX = 1;
	float scaleFactorY = 1;
	BrickState state = BrickState::IDLE;

	bool hasPowerUp = false;
	PowerUp power_UP;                                   // powerUp object
	PowerUpType powerUpType = PowerUpType::NOT_SETTED;  // powerUp type

	/**
	* Constructors
	*/
	Brick() {};
	Brick(std::string _name, int _width, int _height)
		: name(_name), positionX(0.0f), positionY(0.0f), width(_width), height(_height) {}
	Brick(std::string _name, float x, float y, int _width, int _height)
		: name(_name), positionX(x), positionY(y), width(_width), height(_height) {}

	// Update scale factors and brick state
	void scaleBrickUntilCrushed(float deltaTime) {
		scaleFactorX -= 10 * deltaTime;
		scaleFactorY -= 10 * deltaTime;
		if (scaleFactorX <= 0 || scaleFactorY <= 0) {
			state = CRUSHED;
		}
	}

	// construct powerUp under current brick
	void constructPowerUp(float r, float g, float b, PowerUpType type) {
		hasPowerUp = true;
		power_UP = PowerUp(name + "_power_up", (positionX + width / 2.0 - powerUpWidth),
			               (positionY + height / 2.0 - powerUpHeight), powerUpWidth, powerUpHeight);	
		powerUpType = type;
		Mesh* powerUpMesh = ObjectIn2D::CreateRectangle(power_UP.name, glm::vec3(0, 0, 0), power_UP.height,
			                                            power_UP.width, glm::vec3(r, g, b), true);
		power_UP.setMesh(powerUpMesh);
	}

	// reset powerUp (called when the scene is reinitialized)
	void resetPowerUp() {
		if (hasPowerUp) {
			power_UP.captured = false;
			power_UP.positionX = (positionX + width / 2.0 - powerUpWidth);
			power_UP.positionY = (positionY + height / 2.0 - powerUpHeight);
		}
	}
};