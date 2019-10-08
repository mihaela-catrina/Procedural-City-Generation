#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include "Objects.h"
#include "Building.h"
#include "Decoration.h"

class CityView : public SimpleScene {
public:
	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1);
	int randomInt(int min, int max);
	float randomFloat(float LO, float HI);
	void generateRandomStreetsCoordinates();
	void generateRandomStreets();
	void renderStreets();
	Building generateBuildingBetweenCoord(float x1, float x2, float z1, float z2);
	void generateBuildings();
	void renderBuildings();
	void renderDecorations();
	void putGrass(float x1, float x2, float z1, float z2);
	void renderTrees();
	void renderWalls();
	void generateTrees();

public:
	std::unordered_map<std::string, Texture2D*> mapTextures;
	std::vector<int> streetsOnX;
	std::vector<int> streetsOnZ;
	std::vector<Building> buildings;
	std::vector<std::string> textures;
	std::vector<int> prob = { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
	std::vector<Decoration> decorations;
	std::vector<std::tuple<float, float, float>> trees;
};