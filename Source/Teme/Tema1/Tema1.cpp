#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;


Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	sResolution.first = (float)resolution.x;
	sResolution.second = (float)resolution.y;
	createSceneWalls(window->props.resolution);
	createBricks(window->props.resolution);
	createBall(window->props.resolution);
	createPlatform(window->props.resolution);
	createLifesArray(window->props.resolution);
	createBullets();
	createGameOverFace();
	createCheckSign();
	width = window->props.resolution.x;
	height = window->props.resolution.y;
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{	
	if (lifes > 0) {
		
		if (gameState == GameState::NORMAL) {
			drawSceneWalls();
			drawPlatform();
			if (!ballOnThePlatform) {
				checkCollision();
				checkTouchPlatform();
				updateBallPosition(deltaTimeSeconds);
			}
			if (ball.isOnScene) {
				drawBall(deltaTimeSeconds);
			}
			else {
				updatePowerAndRestart();
			}
			drawPower();
			drawSceneBricks(deltaTimeSeconds);
			verifySuccess();
		}
		else if (gameState == GameState::WEAPON_POWER) {
			drawSceneWalls();
			drawPlatform();
			drawBullets(deltaTimeSeconds, fired);
			fired = false;
			timer -= deltaTimeSeconds;
			if (timer <= 0) {
				gameState = GameState::NORMAL;
				timer = 2;
				resetBullets();
			}
			drawPower();
			drawSceneBricks(deltaTimeSeconds);
			verifySuccess();
		}
		else if (gameState == GameState::WIN) {
			drawCheckSign();
		}
	}
	else {
		drawGameOverFace();
	}
}

void Tema1::FrameEnd()
{
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
};

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
	}
};

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	platform.positionX = mouseX * ((float)width / sResolution.first) - platformLength / 2.0f;
	if (ballOnThePlatform) {
		ball.angle = PI / 2.0f;
		ball.positionX = mouseX * ((float)width / sResolution.first);
		ball.positionY = platformHeightOnScene + platformHeight + ballRadius;
	}

};

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

	// add mouse button press event
	if (button == GLFW_MOUSE_BUTTON_2) {
		if (lifes <= 0 || gameState == GameState::WIN) {
			gameState = GameState::NORMAL;
			lifes = 3;
			Reinitialize();
			return;
		}
		ballOnThePlatform = false;
	}
	else {
		if (gameState == GameState::WEAPON_POWER) {
			fired = true;
		}
	}

};

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Tema1::OnWindowResize(int width, int height)
{
	// treat window resize event
	sResolution.first = width;
	sResolution.second = height;
}
