#include "Ball.h"

void Ball::createMeshes(std::unordered_map<std::string, Mesh*>& meshes)
{
	Mesh* baseMesh = new Mesh(GAMEBALL);
	baseMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[baseMesh->GetMeshID()] = baseMesh;
}

void Ball::createTextures(std::unordered_map<std::string, Texture2D*>& mapTextures)
{
	const std::string textureLoc = "Source/Teme/Tema2/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball1.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball1"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball2.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball2"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball3.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball3"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball4.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball4"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball5.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball5"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball6.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball6"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball7.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball7"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball8.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball8"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball9.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball9"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball10.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball10"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball11.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball11"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball12.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball12"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball13.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball13"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball14.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball14"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Ball15.jpg").c_str(), GL_REPEAT);
		mapTextures["Ball15"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "BallCue.jpg").c_str(), GL_REPEAT);
		mapTextures["BallCue"] = texture;
	}

}

void Ball::setScallingFactors()
{
	this->scaleX = 0.11;
	this->scaleY = 0.11;
	this->scaleZ = 0.11;
	radius = scaleX / 2.0f;
}

void Ball::setTranslations(float x, float y, float z)
{
	this->translateX = x;
	this->translateY = y;
	this->translateZ = z;
}

bool Ball::collisionWithOtherBall(Ball* ball) {
	float dt = 0.005;
	if (ball->velocity == glm::vec3(0, 0, 0) && this->velocity == glm::vec3(0, 0, 0)) return false;
	glm::vec3 distance = glm::vec3(this->translateX, this->translateY, this->translateZ) -
					     glm::vec3(ball->translateX, ball->translateY, ball->translateZ);
	glm::vec3 posA = glm::vec3(this->translateX, this->translateY, this->translateZ);
	glm::vec3 posB = glm::vec3(ball->translateX, ball->translateY, ball->translateZ);
	glm::vec3 nextPosA = posA + this->velocity * dt;
	glm::vec3 nextPosB = posB + ball->velocity * dt;
	glm::vec3 distanceNow = posA - posB;
	glm::vec3 distanceAfter = nextPosA - nextPosB;
	if (glm::length(distanceNow) <= this->radius + ball->radius) {
		return true;
	} else {
		return false;
	}
}

void Ball::updateBallsWhenHit(Ball *ball) {
	float tmp;
	glm::vec3 normal, direction, v1n, v1t, v2n, v2t;
	glm::vec3 currentPosition = glm::vec3(this->translateX, this->translateY, this->translateZ);
	glm::vec3 checkedBallPosition = glm::vec3(ball->translateX, ball->translateY, ball->translateZ);
	direction = checkedBallPosition - currentPosition;
	normal = glm::normalize(direction);
	glm::vec3 sumVelocity = this->velocity + ball->velocity;

	tmp = this->radius - glm::length(normal) / 2;

	v1n = normal * glm::dot(normal, this->velocity);
	v1t = this->velocity - v1n;

	normal = normal * (-1.0f);
	v2n = normal * glm::dot(normal, ball->velocity);
	v2t = ball->velocity - v2n;

	this->velocity = v2n + v1t;
	ball->velocity = v1n + v2t;

	currentPosition = currentPosition - normal * tmp / 10.0f;
	checkedBallPosition = checkedBallPosition + normal * tmp / 10.0f;
	this->translateX = currentPosition.x;
	this->translateY = currentPosition.y;
	this->translateZ = currentPosition.z;

	ball->translateX = checkedBallPosition.x;
	ball->translateY = checkedBallPosition.y;
	ball->translateZ = checkedBallPosition.z;
}
