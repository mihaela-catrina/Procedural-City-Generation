#pragma once
#include "GameScene.h"
#include "ObjectIn2D.h"
#include "Transformations.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include <Component/Transform/Transform.h>

glm::vec2 closest;                                        // closest point where the collision occured

using namespace EngineComponents;

COLOR red = { 1, 0, 0 };
COLOR green = { 0, 1, 0 };
COLOR black = { 30 / 255.0, 30 / 255.0, 21 / 255.0 };
COLOR brown = { 128 / 255.0, 0 / 255.0, 0 / 255.0 };
COLOR coolblue = { 70 / 255.0, 130 / 255.0, 180 / 255.0 };
COLOR silver = { 128 / 255.0, 128 / 255.0, 128 / 255.0 };
COLOR yellow = { 1, 1, 0 };
COLOR teal = { 160 / 255.0, 80 / 255.0, 23 / 255.0 };
COLOR lblue = { 51 / 255.0, 153 / 255.0, 255 / 255.0 };
COLOR white = { 1, 1, 1 };
COLOR indigo = { 75 / 255.0, 0 / 255.0, 150 / 255.0 };


void GameScene::createSceneWalls(glm::ivec2 sceneResolution)
{
	// Create walls meshes
	int viewHeight = sceneResolution.y;
	int viewWidth  = sceneResolution.x;
	Wall leftWall = Wall("leftWall", 0, 80, wallSize, viewHeight);
	Mesh* leftWallMesh = ObjectIn2D::CreateRectangle(leftWall.name, glm::vec3(leftWall.positionX, leftWall.positionY, 0),
													 leftWall.height, leftWall.width, glm::vec3(teal.r, teal.g, teal.b), true);
	walls.push_back(leftWall);
	AddMeshToList(leftWallMesh);

	Wall rightWall = Wall("rightWall", viewWidth - wallSize, 80, wallSize, viewHeight);
	Mesh* rightWallMesh = ObjectIn2D::CreateRectangle(rightWall.name, glm::vec3(rightWall.positionX, rightWall.positionY, 0),
													  rightWall.height, rightWall.width, glm::vec3(teal.r, teal.g, teal.b), true);
	walls.push_back(rightWall);
	AddMeshToList(rightWallMesh);

	Wall upperWall = Wall("upperWall", 0, viewHeight - wallSize, viewWidth, wallSize);
	Mesh* upperWallMesh = ObjectIn2D::CreateRectangle(upperWall.name, glm::vec3(upperWall.positionX, upperWall.positionY, 0),
													  upperWall.height, upperWall.width, glm::vec3(teal.r, teal.g, teal.b), true);
	walls.push_back(upperWall);
	AddMeshToList(upperWallMesh);
}

void GameScene::drawSceneWalls()
{
	RenderMesh2D(meshes["leftWall"], shaders["VertexColor"], glm::mat3(1));
	RenderMesh2D(meshes["rightWall"], shaders["VertexColor"], glm::mat3(1));
	RenderMesh2D(meshes["upperWall"], shaders["VertexColor"], glm::mat3(1));
}

void GameScene::createBricks(glm::ivec2 sceneResolution)
{
	int viewHeight = sceneResolution.y;
	int viewWidth = sceneResolution.x;
	bricks.resize(noBricksPerLine, std::vector<Brick>(noBricksPerColon));
	brickSize = glm::ivec2((viewHeight - wallSize - offsetOnYUp- offsetOnYDown - spaceBetweenBricks * (noBricksPerColon - 1)) / noBricksPerColon,
						   (viewWidth - 2 * wallSize - 2 * offsetOnX - spaceBetweenBricks * (noBricksPerLine - 1)) / noBricksPerLine);
	// Create brick meshes
	for (int i = 0; i < noBricksPerLine; i++) {
		for (int j = 0; j < noBricksPerColon; j++) {
			std::string name = "brick" + std::to_string(i) + std::to_string(j);
			Brick brick = Brick(name, brickSize[1], brickSize[0]);
			brick.positionX = wallSize + offsetOnX + i * (brickSize[1] + spaceBetweenBricks);
			brick.positionY = offsetOnYDown + j * (brickSize[0] + spaceBetweenBricks);
			Mesh* brickMesh = ObjectIn2D::CreateRectangle(brick.name, glm::vec3(0, 0, 0), brick.height, brick.width, glm::vec3(brown.r, brown.g, brown.b), true);
			// set no_reflection with walls power up
			if ((i+j) % 6 == 0) {
				brick.constructPowerUp(red.r, red.g, red.b, PowerUpType::NO_REFLECTION_ON_BRICK_COLLISION);
				AddMeshToList(brick.power_UP.getMesh());
			}
			// set weapon power up
			if (i == j) {
				brick.constructPowerUp(indigo.r, indigo.g, indigo.b, PowerUpType::WEAPON);
				AddMeshToList(brick.power_UP.getMesh());
			}
			bricks[i][j] = brick;
			AddMeshToList(brickMesh);
		}
	}
}

void GameScene::drawSceneBricks(float deltaTimeSeconds)
{
	success = true;
	for (int i = 0; i < noBricksPerLine; i++) {
		for (int j = 0; j < noBricksPerColon; j++) {
			// if current brick was touched by the ball => start to scale this brick
			if (bricks[i][j].state == BrickState::HIT) {
				bricks[i][j].scaleBrickUntilCrushed(deltaTimeSeconds);
			}

			// id brick is HIT or crushed, update powerUp position and state
			if (bricks[i][j].state != BrickState::IDLE) {
				// if the corresponding power up exists and it was not catched yet
				if (bricks[i][j].hasPowerUp && !bricks[i][j].power_UP.captured) {
					bricks[i][j].power_UP.update(deltaTimeSeconds);
					// verify if the player capture this power up
					auto captured = checkCollisonPowerUpPlatform(bricks[i][j].power_UP);
					// set corresponding behaiour
					if (captured) {
						bricks[i][j].power_UP.captured = true;
						if (bricks[i][j].powerUpType == PowerUpType::WEAPON) {
							setWeaponBehaviour();
						}

						if (bricks[i][j].powerUpType == PowerUpType::NO_REFLECTION_ON_BRICK_COLLISION) {
							setNoReflectionBehaviour();
						}
					   
					} else {
						// update powerUp in scene
						glm::mat3 modelMatrix = glm::mat3(1);
						modelMatrix *= Transformations::Translate(bricks[i][j].power_UP.positionX, bricks[i][j].power_UP.positionY);
						modelMatrix *= Transformations::Translate(bricks[i][j].power_UP.width / 2.0, bricks[i][j].power_UP.height / 2.0);
						modelMatrix *= Transformations::Rotate(bricks[i][j].power_UP.angle);
						modelMatrix *= Transformations::Translate((-1) * bricks[i][j].power_UP.width / 2.0, (-1) * bricks[i][j].power_UP.height / 2.0);
						RenderMesh2D(meshes[bricks[i][j].power_UP.name], shaders["VertexColor"], modelMatrix);
					}
				}
			}

			// render powerUp
			if (bricks[i][j].state != BrickState::CRUSHED) {
				success = false;
				std::string name = "brick" + std::to_string(i) + std::to_string(j);
				glm::mat3 modelMatrix = glm::mat3(1);
				modelMatrix *= Transformations::Translate(bricks[i][j].positionX, bricks[i][j].positionY);
				modelMatrix *= Transformations::Translate(bricks[i][j].width / 2.0, bricks[i][j].height / 2.0);
				modelMatrix *= Transformations::Scale(bricks[i][j].scaleFactorX, bricks[i][j].scaleFactorY);
				modelMatrix *= Transformations::Translate((-1)*bricks[i][j].width / 2.0, (-1)*bricks[i][j].height / 2.0);
				RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
			}
		}
	}
}

void GameScene::createBall(glm::ivec2 sceneResolution)
{
	ball = Ball("ball", sceneResolution.x / 2.0f, platformHeightOnScene + platformHeight + ballRadius, ballRadius);
	ball.directionX = 1;
	ball.directionY = 1;
	Mesh *ballMesh = ObjectIn2D::CreateCircle("ball", ballRadius, glm::vec3(silver.r, silver.g, silver.b), 0.1, true);
	AddMeshToList(ballMesh);
}

void GameScene::drawBall(float deltaTimeSeconds)
{
	// updat timer
	if (ball.strengthOn) {
		timer -= deltaTimeSeconds;
		if (timer <= 0) {
			ball.strengthOn = false;
			timer = 2;
		}
	}
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(ball.positionX, ball.positionY);
	RenderMesh2D(meshes["ball"], shaders["VertexColor"], modelMatrix);
}

void GameScene::createPlatform(glm::ivec2 sceneResolution)
{
	platform = Platform("platform", sceneResolution.x / 2.0f - platformLength / 2.0f, platformHeightOnScene, platformLength, platformHeight);
	Mesh *platMesh = ObjectIn2D::CreatePlatform("platform", glm::vec3(0, 0, 0), platform.height, platform.width, glm::vec3(coolblue.r, coolblue.g, coolblue.b), true);
	platform.setMesh(platMesh);
	AddMeshToList(platMesh);
}

void GameScene::drawPlatform()
{
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(platform.positionX, platform.positionY);
	RenderMesh2D(meshes[platform.name], shaders["VertexColor"], modelMatrix);
}

void GameScene::createLifesArray(glm::ivec2 sceneResolution)
{
	for (int i = 0; i < lifes; i++) {
		std::string name = "life" + std::to_string(i);
		auto powerBall = Ball(name, 15 + i * 3 * ballRadius, 10, ballRadius);
		Mesh *powerBallMesh = ObjectIn2D::CreateCircle(powerBall.name, ballRadius, glm::vec3(red.r, red.g, red.b), 0.1, true);
		power.push_back(powerBall);
		AddMeshToList(powerBallMesh);
	}
}

void GameScene::drawPower()
{
	for (int i = 0; i < lifes; i++) {
		glm::mat3 modelMatrix = glm::mat3(1);
		modelMatrix *= Transformations::Translate(power[i].positionX, power[i].positionY);
		RenderMesh2D(meshes[power[i].name], shaders["VertexColor"], modelMatrix);
	}
}

void GameScene::updateBallPosition(float deltaTimeSeconds)
{
	ball.positionX += ball.directionX * cos(ball.angle) * deltaTimeSeconds * 450;
	ball.positionY += ball.directionY * std::sin(ball.angle) * deltaTimeSeconds * 450;
}

// verify which side of the obj. has been hit to perform proper reflection
void GameScene::updateBallDirection(float objPosX, float objPosY, float width, float height)
{
	if (closest[0] == objPosX && ball.directionX == 1) {
		ball.directionX *= -1;
	}

	if (closest[0] == objPosX + width && ball.directionX == -1) {
		ball.directionX *= -1;
	}

	if (closest[1] == objPosY && ball.directionY == 1) {
		ball.directionY *= -1;
	}

	if (closest[1] == objPosY + height && ball.directionY == -1) {
		ball.directionY *= -1;
	}
}

void GameScene::checkCollision()
{
	if (!ball.isOnScene) return;
	bool collision = false;
	// check collision with the walls
	for (auto &wall : walls) {
		collision = checkBallRectangularObjCollision(wall.positionX, wall.positionY, wall.width, wall.height);
		if (collision) {
			updateBallDirection(wall.positionX, wall.positionY, wall.width, wall.height);
		}
	}

	// check collision with the bricks
	for (int i = 0; i < noBricksPerLine; i++) {
		for (int j = 0; j < noBricksPerColon; j++) {
			if (bricks[i][j].state == BrickState::IDLE) {
				auto collision = checkBallBrickCollision(i, j);
				if (collision) return;
			}
		}
	}
}

void GameScene::checkTouchPlatform()
{
	// verify if the ball touches the platform
	if (ball.positionX >= platform.positionX && ball.positionX <= platform.positionX + platform.width) {
		if (ball.positionY - ball.radius <= platform.positionY + platform.height) {
			if (ball.positionX < platform.positionX + platform.width / 2.0f) {
				ball.directionX = -1;
				ball.angle = (ball.positionX - platform.positionX) * (PI / 2) / (platform.width / 2.0f);
			}
			else {
				ball.angle = (platform.positionX + platform.width - ball.positionX) * (PI / 2) / (platform.width / 2.0f);
				ball.directionX = 1;
			}
			ball.directionY = 1;
			return;
		}
	}

	// verify if the ball falls off of the platform
	if (ball.positionY - ball.radius <= 0 || ball.positionX < 0 || ball.positionX  > sResolution.first) {
		ball.isOnScene = false;
		return;
	}
}

// check the collision with one brick
bool GameScene::checkBallBrickCollision(int i, int j)
{
	Brick *brick = &bricks[i][j];
	bool collision = checkBallRectangularObjCollision(brick->positionX, brick->positionY, brick->width, brick->height);
	
	if (collision) {
		brick->state = BrickState::HIT;
		if (ball.strengthOn) return collision;
		updateBallDirection(brick->positionX, brick->positionY, brick->width, brick->height);
	}
	return collision;
}

// cheack ball - rectangle collision
bool GameScene::checkBallRectangularObjCollision(float posX, float posY, float width, float height)
{
	glm::vec2 ballCenter(ball.positionX, ball.positionY);
	glm::vec2 rectangleCenter(posX + width / 2.0, posY + height / 2.0);
	// get the difference between centers (vector)
	glm::vec2 distance = ballCenter - rectangleCenter;
	glm::vec2 clampedVec = glm::clamp(distance, glm::vec2((-1) * width / 2.0, (-1) * height / 2.0), glm::vec2(width / 2.0, height / 2.0));
	// get closest point to the circle center (point on the rectangle)
	closest = rectangleCenter + clampedVec;
	// Compute the vector between closest point and ball center
	distance = closest - ballCenter;
	auto difference = glm::length(distance);
	return difference < ball.radius + 3;
}

bool GameScene::checkCollisonPowerUpPlatform(PowerUp powerUp)
{
	// Collision on x-axis
	bool collisionX = platform.positionX + platform.width >= powerUp.positionX &&
		powerUp.positionX + powerUp.width >= platform.positionX;
	// Collision on y-axis
	bool collisionY = platform.positionY + platform.height >= powerUp.positionY &&
		powerUp.positionY + powerUp.height >= platform.positionY;
	return collisionX && collisionY;
}

// update lives when the ball is lost
void GameScene::updatePowerAndRestart()
{
	platform.positionX = sResolution.first / 2.0f - platformLength / 2.0f;
	platform.positionY = platformHeightOnScene;
	ball.positionX = sResolution.first / 2.0f;
	ball.positionY = platformHeightOnScene + platformHeight + ballRadius;
	lifes--;
	ball.isOnScene = true;
	ballOnThePlatform = true;
}


void GameScene::setWeaponBehaviour()
{
	gameState = GameState::WEAPON_POWER;
	ball.positionX = platform.positionX + platform.width / 2.0;
	ball.positionY = platformHeightOnScene + platformHeight + ballRadius;
	ball.isOnScene = true;
	ballOnThePlatform = true;
}

void GameScene::setNoReflectionBehaviour()
{
	ball.strengthOn = true;
}

void GameScene::createBullets()
{
	for (int i = 0; i < bulletsNumber; i++) {
		std::string name = "bullet" + std::to_string(i);
		auto bullet = Ball(name, 5);
		Mesh *bulletMesh = ObjectIn2D::CreateCircle(bullet.name, bullet.radius, glm::vec3(silver.r, silver.g, silver.b), 0.1, true);
		bullets.insert({ bullet.name, bullet });
		bulletsStack.push(bullet);
		AddMeshToList(bulletMesh);
	}
}

void GameScene::drawBullets(float deltaTime, bool fired)
{
	if (fired) {
		int rangeNumberBullets = 3 - 1 + 1;
		int numBullets = rand() % rangeNumberBullets + 1;

		int positionRange = platform.width - 0 + 1;

		// generate a number of bullets to use from the unused bullets
		for (int i = 0; i < numBullets; i++) {
			int position = rand() % positionRange + 1;
			if (bulletsStack.empty()) break;
			Ball bullet = bulletsStack.top();
			auto posX = platform.positionX + 5 + position + i * bullet.radius;
			auto posY = platform.positionY + platform.height;
			bullets[bullet.name].positionX = posX;
			bullets[bullet.name].positionY = posY;
			bulletsStack.pop();
			if (usedBullets.count(bullet.name)) {
				usedBullets[bullet.name] = true;
			}
			else {
				usedBullets.insert({ bullet.name, true });
			}
		}
	}

	// update bullets on canvas and check their collision with the bricks
	for (auto& pair : usedBullets) {
		if (pair.second) {
			auto bulletName =  pair.first;
			glm::mat3 modelMatrix = glm::mat3(1);
			bullets[bulletName].positionY += 700 * deltaTime;
			for (int i = 0; i < noBricksPerLine; i++) {
				for (int j = 0; j < noBricksPerColon; j++) {
					if (bricks[i][j].state == BrickState::IDLE) {
						if (bullets[bulletName].positionY >= bricks[i][j].positionY &&
							bullets[bulletName].positionY <= bricks[i][j].positionY + bricks[i][j].height &&
							bullets[bulletName].positionX >= bricks[i][j].positionX &&
							bullets[bulletName].positionX <= bricks[i][j].positionX + bricks[i][j].width) {
							bricks[i][j].state = BrickState::HIT;
							pair.second = false;
						}
					}
				}
			}
			
			modelMatrix *= Transformations::Translate(bullets[bulletName].positionX, bullets[bulletName].positionY);
			RenderMesh2D(meshes[bulletName], shaders["VertexColor"], modelMatrix);

			// if a bullet exceed the canvas it can be used again
			if (bullets[pair.first].positionY >= sResolution.second) {
				pair.second = false;
				bulletsStack.push(bullets[pair.first]);
			}
		}
	}
}

void GameScene::resetBullets()
{
	// restore bullets containers
	usedBullets.clear();
	while (!bulletsStack.empty()) bulletsStack.pop();
	for (const auto& b : bullets) {
		bulletsStack.push(b.second);
	}
}

void GameScene::createCheckSign()
{
	Brick low = Brick("signLow", sResolution.first / 2, 200, 20, 200);
	Mesh *lowHalf = ObjectIn2D::CreateRectangle("signLow", glm::vec3(0, 0, 0), low.height, low.width, glm::vec3(green.r, green.g, green.b), true);
	AddMeshToList(lowHalf);
	checkSign.push_back(low);

	Brick sup = Brick("signSup", sResolution.first / 2, 200, 20, 500);
	Mesh *supHalf = ObjectIn2D::CreateRectangle("signSup", glm::vec3(0, 0, 0), sup.height, sup.width, glm::vec3(green.r, green.g, green.b), true);
	AddMeshToList(supHalf);
	checkSign.push_back(sup);
}

void GameScene::drawCheckSign()
{
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(checkSign[0].positionX, checkSign[0].positionY);
	modelMatrix *= Transformations::Rotate((-1) * PI / 4);
	RenderMesh2D(meshes[checkSign[0].name], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(checkSign[1].positionX, checkSign[1].positionY);
	modelMatrix *= Transformations::Rotate(PI / 4);
	RenderMesh2D(meshes[checkSign[1].name], shaders["VertexColor"], modelMatrix);
}

void GameScene::createGameOverFace()
{
	Mesh *face = ObjectIn2D::CreateCircle("face", 50, glm::vec3(yellow.r, yellow.g, yellow.b), 0.1, true);
	AddMeshToList(face);
	Mesh *leftEye = ObjectIn2D::CreateCircle("leftEye", 10, glm::vec3(black.r, black.g, black.b), 0.1, true);
	AddMeshToList(leftEye);
	Mesh *leftEyeP = ObjectIn2D::CreateCircle("leftEyeP", 5, glm::vec3(coolblue.r, coolblue.g, coolblue.b), 0.1, true);
	AddMeshToList(leftEyeP);
	Mesh *rightEye = ObjectIn2D::CreateCircle("rightEye", 10, glm::vec3(black.r, black.g, black.b), 0.1, true);
	AddMeshToList(rightEye);
	Mesh *rightEyeP = ObjectIn2D::CreateCircle("rightEyeP", 5, glm::vec3(coolblue.r, coolblue.g, coolblue.b), 0.1, true);
	AddMeshToList(rightEyeP);

	Mesh *mouth = ObjectIn2D::CreateSemicircle("mouth", 10, glm::vec3(red.r, red.g, red.b), 0.1);
	AddMeshToList(mouth);
}

void GameScene::drawGameOverFace()
{
	glm::mat3 modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(sResolution.first / 2.0 - 20, sResolution.second / 2.0);
	RenderMesh2D(meshes["leftEyeP"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(sResolution.first / 2.0 + 20, sResolution.second / 2.0 - 5);
	RenderMesh2D(meshes["rightEyeP"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(sResolution.first / 2.0 - 20, sResolution.second / 2.0 + 12);
	RenderMesh2D(meshes["leftEye"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(sResolution.first / 2.0 + 20, sResolution.second / 2.0 + 12);
	RenderMesh2D(meshes["rightEye"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(sResolution.first / 2.0, sResolution.second / 2.0 - 25);
	RenderMesh2D(meshes["mouth"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transformations::Translate(sResolution.first / 2.0, sResolution.second / 2.0);
	RenderMesh2D(meshes["face"], shaders["VertexColor"], modelMatrix);

}

// restore game
void GameScene::Reinitialize() {
	for (int i = 0; i < noBricksPerLine; i++) {
		for (int j = 0; j < noBricksPerColon; j++) {
			bricks[i][j].state = BrickState::IDLE;
			bricks[i][j].resetPowerUp();
			bricks[i][j].scaleFactorX = 1;
			bricks[i][j].scaleFactorY = 1;
		}
	}
}

void GameScene::verifySuccess() {
	if (success) gameState = GameState::WIN;
}