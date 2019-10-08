#pragma once
#include "ObjectTema2.h"
#include <Component/SimpleScene.h>
constexpr auto GAMEBALL = "ball";

class Ball : public ObjectTema2, SimpleScene {
public:
	float radius;
	static void createMeshes(std::unordered_map<std::string, Mesh*> &meshes);
	static void createTextures(std::unordered_map<std::string, Texture2D*> &mapTextures);
	void setScallingFactors();
	void setTranslations(float x, float y, float z);
	bool collisionWithOtherBall(Ball* ball);
	void updateBallsWhenHit(Ball *ball);

	glm::vec3 velocity = glm::vec3(0, 0, 0);
	glm::vec3 orientation = glm::vec3(0, 0, 0);

	const float mass = 1;
	bool isInPocket = false;
};