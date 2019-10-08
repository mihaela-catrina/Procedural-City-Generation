#include "Tema3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = Objects::CreateRectangle("ground", glm::vec3(10, -0.001, 10), 20, 20, glm::vec2(10, 10));
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = Objects::CreateRectangle("skyLeft", glm::vec3(0, 0, 0), 1, 1, glm::vec2(1, 5));
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = Objects::CreateRectangle("skyLeftBig", glm::vec3(0, 0, 0), 60, 60, glm::vec2(1, 1));
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = Objects::CreateRectangle("grass", glm::vec3(0, 0, 0), 20, 20, glm::vec2(20, 20));
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = Objects::CreateRectangle("grass", glm::vec3(0, 0, 0), 20, 20, glm::vec2(20, 20));
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* baseMesh = new Mesh("decoration3");
		baseMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "tree.obj");
		meshes[baseMesh->GetMeshID()] = baseMesh;

	}

	LoadTextures();

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderTema3");
		shader->AddShader("Source/Teme/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Teme/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	generateRandomStreets();
	generateBuildings();
	generateTrees();
}

void Tema3::FrameStart()
{
}

void Tema3::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, 0, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderSimpleMesh(meshes["ground"], shaders["ShaderTema3"], glm::mat4(1), mapTextures["groundTexture"]);

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, 0, 10));
	RenderSimpleMesh(meshes["grass"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(30, 0, 10));
	RenderSimpleMesh(meshes["grass"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 0, 30));
	RenderSimpleMesh(meshes["grass"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 0, -10));
	RenderSimpleMesh(meshes["grass"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, 0, -10));
	RenderSimpleMesh(meshes["grass"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(30, 0, -10));
	RenderSimpleMesh(meshes["grass"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-10, 0, 30));
	RenderSimpleMesh(meshes["grass"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(30, 0, 30));
	RenderSimpleMesh(meshes["grass"], shaders["ShaderTema3"], modelMatrix, mapTextures["grass"]);

	//top
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 30, 30));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(270), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 0, 1));
	RenderSimpleMesh(meshes["skyLeftBig"], shaders["ShaderTema3"], modelMatrix, mapTextures["skyLeft"]);

	//right
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(40, 30, 10));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 0, 1));
	RenderSimpleMesh(meshes["skyLeftBig"], shaders["ShaderTema3"], modelMatrix, mapTextures["skyLeft"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-20, 30, 10));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 0, 1));
	RenderSimpleMesh(meshes["skyLeftBig"], shaders["ShaderTema3"], modelMatrix, mapTextures["skyLeft"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 30, -20));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 0, 1));
	RenderSimpleMesh(meshes["skyLeftBig"], shaders["ShaderTema3"], modelMatrix, mapTextures["skyLeft"]);

	renderStreets();
	renderBuildings();
	renderDecorations();
	renderWalls();
	renderTrees();
}

void Tema3::FrameEnd()
{
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
};

void Tema3::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
	}
};

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Tema3::OnWindowResize(int width, int height)
{
	// treat window resize event
}


void Tema3::LoadTextures() 
{
	const std::string textureLoc = "Source/Teme/Tema3/Textures/";
	Texture2D *texture = new Texture2D();
	texture->Load2D((textureLoc + "paving.png").c_str(), GL_REPEAT);
	mapTextures["groundTexture"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "131_dirt road texture-seamless.jpg").c_str(), GL_REPEAT);
	mapTextures["streetTextureOnX"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "131_dirt road texture-seamless.png").c_str(), GL_REPEAT);
	mapTextures["streetTextureOnZ"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "127_road texture-seamless.jpg").c_str(), GL_REPEAT);
	mapTextures["interStreets"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "roofTexture.png").c_str(), GL_REPEAT);
	mapTextures["roofTexture"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "sky.png").c_str(), GL_REPEAT);
	mapTextures["skyLeft"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "grass.png").c_str(), GL_REPEAT);
	mapTextures["grass"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "decoration1.png").c_str(), GL_REPEAT);
	mapTextures["decoration1"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "decoration2.png").c_str(), GL_REPEAT);
	mapTextures["decoration2"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "wall.png").c_str(), GL_REPEAT);
	mapTextures["wall"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "bark.png").c_str(), GL_REPEAT);
	mapTextures["bark"] = texture;

	texture = new Texture2D();
	texture->Load2D((textureLoc + "leaf.png").c_str(), GL_REPEAT);
	mapTextures["leaf"] = texture;

	for (int i = 1; i <= 12; i++) {
		texture = new Texture2D();
		texture->Load2D((textureLoc + "building" + std::to_string(i) + ".png").c_str(), GL_REPEAT);
		mapTextures["building" + std::to_string(i)] = texture;
	}
}