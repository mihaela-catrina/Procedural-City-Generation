#include "Cue.h"
constexpr auto CUE = "cue";

void Cue::createMesh(std::unordered_map<std::string, Mesh*>& meshes)
{
	Mesh* baseMesh = new Mesh(CUE);
	baseMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[baseMesh->GetMeshID()] = baseMesh;
}

void Cue::createTexture(std::unordered_map<std::string, Texture2D*>& mapTextures)
{
	const std::string textureLoc = "Source/Teme/Tema2/Textures/";

	Texture2D* texture = new Texture2D();
	texture->Load2D((textureLoc + "cueWood.jpg").c_str(), GL_REPEAT);
	mapTextures["cue"] = texture;
}

void Cue::setScallingFactors()
{
	this->scaleX = 0.03;
	this->scaleY = 0.03;
	this->scaleZ = 2;
}

void Cue::setTranslations(float x, float y, float z)
{
	this->translateX = x;
	this->translateY = y;
	this->translateZ = z;
}

void Cue::setRotation(float ax, float ay, float az)
{
	this->angularStepOX = ax;
	this->angularStepOY = ay;
	this->angularStepOZ = az;
}

void Cue::setForce(float cueTime, float speed) {
	float distance = cueTime * 2;
	force = distance * 0.01;
}
