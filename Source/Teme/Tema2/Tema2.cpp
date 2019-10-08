#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "3DTransform.h"

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	camera = new Camera();
	camera->Set(glm::vec3(0, 2, 4.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	polygonMode = GL_FILL;

	players[1].playerType = NONE;
	players[2].playerType = NONE;
	players[1].playerNo = 1;
	players[2].playerNo = 2;


	table.createMeshes(meshes);
	table.createTextures(mapTextures);
	table.setHeight();
	table.setLength();
	table.setWidth();

	Ball::createMeshes(meshes);
	Ball::createTextures(mapTextures);
	setInitialBallsPosition();

	cue.createMesh(meshes);
	cue.createTexture(mapTextures);
	setCue();

	Mesh* floorMesh = new Mesh("floor");
	floorMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
	meshes[floorMesh->GetMeshID()] = floorMesh;

	const std::string textureLoc = "Source/Teme/Tema2/Textures/";
	Texture2D *texture = new Texture2D();
	texture->Load2D((textureLoc + "Dirtbl.jpg").c_str(), GL_REPEAT);
	mapTextures["floorTexture"] = texture;

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Teme/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Teme/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	
		// create a shader for cue animation
		shader = new Shader("ShaderCueTema2");
		shader->AddShader("Source/Teme/Tema2/Shaders/CueShader/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Teme/Tema2/Shaders/CueShader/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	printf("First player %d\n", currentPlayer);
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	glEnable(GL_TEXTURE_2D);
	drawFloor();
	drawTable();
	checkCollisions();
	checkInPockets();
	updateCueBall();
	updateBalls();
	showStatus();
	if (areBallsStatic()) {
		if (gameState == UPDATING) {
			gameState = SLEEP;
			if (ballIn == false) {
				switchPlayer();
			}
			else {
				ballIn = false;
			}
			printed = false;
		}
	}
	drawBalls();
	if (camera->type == ThirdPerson) {
		drawCue();
	}
}


void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && !window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		if (gameState == START || gameState == SLEEP) {
			if (window->KeyHold(GLFW_KEY_D)) {
				cueBall.translateX += deltaTime;
				if (cueBall.translateX >= table.width / 2.0f - cueBall.radius) {
					cueBall.translateX = table.width / 2.0f - cueBall.radius;
				}
			}

			if (window->KeyHold(GLFW_KEY_A)) {
				cueBall.translateX -= deltaTime;
				if (cueBall.translateX <= (-1)*table.width / 2.0f + cueBall.radius) {
					cueBall.translateX = (-1)*table.width / 2.0f + cueBall.radius;
				}
			}

			if (window->KeyHold(GLFW_KEY_W)) {
				cueBall.translateZ -= deltaTime;
				if (gameState == SLEEP) {
					if (cueBall.translateZ <= (-1) * table.length / 2.0f + cueBall.radius) {
						cueBall.translateZ = (-1) * table.length / 2.0f + cueBall.radius;
					}
				}
				else
				{
					if (cueBall.translateZ <= table.length / 3.0f + cueBall.radius) {
						cueBall.translateZ = table.length / 3.0f + cueBall.radius;
					}
				}
			}

			if (window->KeyHold(GLFW_KEY_S)) {
				cueBall.translateZ += deltaTime;
				if (cueBall.translateZ >= table.length / 2.0f - cueBall.radius) {
					cueBall.translateZ = table.length / 2.0f - cueBall.radius;
				}
			}
		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// translate the camera forward
			camera->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// translate the camera to the left
			camera->TranslateRight((-1)*cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// translate the camera backwards
			camera->TranslateForward((-1) * cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// translate the camera to the right
			camera->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// translate the camera down
			camera->TranslateUpword((-1) * cameraSpeed*deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// translate the camera up
			camera->TranslateUpword(cameraSpeed*deltaTime);
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		camera->type = ThirdPerson;
		camera->Set(glm::vec3(0, 2, 4.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
		cameraRotationAlongOy = 0;
		if (gameState == START) {
			gameState = CUE_ON_SCENE_START;
		} else if(gameState == SLEEP)
		{
			gameState = CUE_ON_SCENE;
		}
		if (areBallsStatic()) {
			charge = IDLE;
		}
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	float sensivityOX = 0.002f;
	float sensivityOY = 0.002f;

	// add mouse move event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		camera->RotateOY(sensivityOY * -(float)deltaX, glm::vec3(cueBall.translateX, cueBall.translateY, cueBall.translateZ));
		camera->RotateOX(sensivityOX * -(float)deltaY, glm::vec3(cueBall.translateX, cueBall.translateY, cueBall.translateZ));

		if (camera->type == ThirdPerson) {
			cameraRotationAlongOx += sensivityOX * -(float)deltaY;
			cameraRotationAlongOy += sensivityOY * -(float)deltaX;
		}
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (gameState == CUE_ON_SCENE || gameState == CUE_ON_SCENE_START) {
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			charge = CHARGE;
			gameState = CHARGE_STATE;
		}
	}
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if (gameState == CHARGE_STATE) {
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			timeAtRelease = cueTime;
			charge = RELEASE;
			gameState = CUE_BALL_JUST_HIT;
			setCue();
			camera->Set(glm::vec3(0, 6.2, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1));
			projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
		}
	}
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
