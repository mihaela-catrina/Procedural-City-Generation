#pragma once
#include "ObjectTema2.h"
#include "Ball.h"

class Pocket : public ObjectTema2 {
public:
	float radius = 0;

	bool checkBallInPocket(Ball *ball) {
		if (ball->isInPocket) return false;
		glm::vec3 ballPos = glm::vec3(ball->translateX, ball->translateY, ball->translateZ);
		glm::vec3 pocketPos = glm::vec3(this->translateX, this->translateY, this->translateZ);

		glm::vec3 distance = pocketPos - ballPos;
		if (glm::length(distance) < (this->radius + ball->radius - 0.2))
			return true;
		else
			return false;
	}

	void updateBallPositionInPocket(Ball *ball) {
		ball->translateX = this->translateX;
		ball->translateY = this->translateY - 0.1;
		ball->translateZ = this->translateZ;
		ball->isInPocket = true;
		ball->velocity = glm::vec3(0, -0.1, 0);
	}
};