#include "CityView.h"
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <Core/Engine.h>

void CityView::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		//activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		//Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		//Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


int CityView::randomInt(int min, int max) //range : [min, max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

float CityView::randomFloat(float LO, float HI) //range : [min, max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));;
}

void CityView::generateRandomStreetsCoordinates()
{
	int nrStreetsOnX = randomInt(6, 9);
	int nrStreetsOnZ = randomInt(5, 9);

	int i = 0;
	while(i < nrStreetsOnX) {
		int x = randomFloat(1, 20);
		bool takeIt = true;
		for (auto v : streetsOnX) {
			if (fabs(v - x) < 1.5) {
				takeIt = false;
				break;
			}
		}
		if (takeIt) {
			streetsOnX.push_back(x);
			i++;
		}
	}

	i = 0;
	while (i < nrStreetsOnZ) {
		int x = randomFloat(1, 20);
		bool takeIt = true;
		for (auto v : streetsOnZ) {
			if (fabs(v - x) < 1) {
				takeIt = false;
				break;
			}
		}
		if (takeIt) {
			streetsOnZ.push_back(x);
			i++;
		}
	}
}

void CityView::generateRandomStreets()
{
	generateRandomStreetsCoordinates();
	for (auto val : streetsOnX) {
		Mesh* mesh = Objects::CreateRectangle("streetX" + std::to_string(val), glm::vec3(val, 0.005, 10), 0.4f, 20.0f, glm::vec2(1, 20));
		meshes[mesh->GetMeshID()] = mesh;
	}

	for (auto val : streetsOnZ) {
		Mesh* mesh = Objects::CreateRectangle("streetZ" + std::to_string(val), glm::vec3(10, 0.01, val), 20.0f, 0.4f, glm::vec2(20, 1));
		meshes[mesh->GetMeshID()] = mesh;
	}

	for (auto valX : streetsOnX) {
		for (auto valZ : streetsOnZ) {
			Mesh* mesh = Objects::CreateRectangle("street" + std::to_string(valX) + std::to_string(valZ), glm::vec3(valX, 0.012, valZ), 0.4f, 0.41f, glm::vec2(1, 1));
			meshes[mesh->GetMeshID()] = mesh;
		}
	}

	std::sort(streetsOnX.begin(), streetsOnX.end());
	std::sort(streetsOnZ.begin(), streetsOnZ.end());
}

void CityView::renderStreets()
{
	for (auto val : streetsOnX) {
		//glm::mat4 modelMatrix;
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
		RenderSimpleMesh(meshes["streetX" + std::to_string(val)], shaders["ShaderTema3"], glm::mat4(1), mapTextures["streetTextureOnZ"]);
	}

	for (auto val : streetsOnZ) {
		RenderSimpleMesh(meshes["streetZ" + std::to_string(val)], shaders["ShaderTema3"], glm::mat4(1), mapTextures["streetTextureOnX"]);
	}

	for (auto valX : streetsOnX) {
		for (auto valZ : streetsOnZ) {
			RenderSimpleMesh(meshes["street" + std::to_string(valX) + std::to_string(valZ)], shaders["ShaderTema3"], glm::mat4(1), mapTextures["interStreets"]);
		}
	}
}

Building CityView::generateBuildingBetweenCoord(float x1, float x2, float z1, float z2)
{
	float distX = fabs(x2 - x1);
	float distZ = fabs(z2 - z1);
	float min = std::min(distX, distZ);
	int nrBuildX = (int)(distX / (min + 0.2));
	int nrBuildZ = (int)(distZ / (min + 0.2));
	float buildingRadius = min / 2.0f;
	if (buildingRadius > 0.4) buildingRadius -= 0.1;

	if (nrBuildX >= 2) {
		float size = distX / nrBuildX;
		for (int i = 0; i < nrBuildX; i++) {
			int buildingFaces = randomInt(4, 13);
			float height = randomFloat(1, 3);
			glm::vec3 center = glm::vec3(x1 + i * size + size / 2.0f, 0, z1 + distZ / 2.0f);
			std::pair<Mesh*, Mesh*> building = Objects::CreateBuilding("Building" + std::to_string(buildings.size()), buildingRadius, center, buildingFaces, height);
			Building b = Building(building, height, center);
			buildings.push_back(b);
		}
	}
	else if (nrBuildZ >= 2) {
		float size = distZ / nrBuildZ;
		for (int i = 0; i < nrBuildZ; i++) {
			int buildingFaces = randomInt(4, 13);
			float height = randomFloat(1, 3);
			glm::vec3 center = glm::vec3(x1 + distX / 2.0f, 0, z1 + i * size + size / 2.0f);
			std::pair<Mesh*, Mesh*> building = Objects::CreateBuilding("Building" + std::to_string(buildings.size()), buildingRadius, center, buildingFaces, height);
			Building b = Building(building, height, center);
			buildings.push_back(b);
		}
	} else {
		int buildingFaces = randomInt(4, 13);
		float height = randomFloat(1, 3);
		glm::vec3 center = glm::vec3(x1 + distX / 2.0f, 0, z1 + distZ / 2.0f);

		std::pair<Mesh*, Mesh*> building = Objects::CreateBuilding("Building" + std::to_string(buildings.size()), buildingRadius, center, buildingFaces, height);
		Building b = Building(building, height, center);
		return b;
	}
}

void CityView::generateBuildings()
{
	for (int i = 0; i < streetsOnX.size() - 1; i++) {
		int x1 = streetsOnX[i];
		int x2 = streetsOnX[i + 1];
		for (int j = 0; j < streetsOnZ.size() - 1; j++) {
			int z1 = streetsOnZ[j];
			int z2 = streetsOnZ[j + 1];
			int buildBuilding = prob[randomInt(0, prob.size() - 1)];
			if (buildBuilding == 1) {
				Building b = generateBuildingBetweenCoord(x1 + 0.2, x2 - 0.2, z1 + 0.2, z2 - 0.2);
				buildings.push_back(b);
			}
			else {
				putGrass(x1 + 0.2, x2 - 0.2, z1 + 0.2, z2 - 0.2);
			}

		}
	}
	if (streetsOnX[0] > 0.6) {
		for (int j = 0; j < streetsOnZ.size() - 1; j++) {
			int z1 = streetsOnZ[j];
			int z2 = streetsOnZ[j + 1];
			int buildBuilding = prob[randomInt(0, prob.size() - 1)];
			if (buildBuilding) {
				Building b = generateBuildingBetweenCoord(0, streetsOnX[0] - 0.2, z1 + 0.2, z2 - 0.2);
				buildings.push_back(b);
			}
			else {
				putGrass(0, streetsOnX[0] - 0.2, z1 + 0.2, z2 - 0.2);
			}

		}
	}

	if (streetsOnX[streetsOnX.size() - 1] < 19.4) {
		for (int j = 0; j < streetsOnZ.size() - 1; j++) {
			int z1 = streetsOnZ[j];
			int z2 = streetsOnZ[j + 1];
			int buildBuilding = prob[randomInt(0, prob.size() - 1)];
			if (buildBuilding == 1) {
				Building b = generateBuildingBetweenCoord(streetsOnX[streetsOnX.size() - 1] + 0.2, 20, z1 + 0.2, z2 - 0.2);
				buildings.push_back(b);
			}
			else {
				putGrass(streetsOnX[streetsOnX.size() - 1] + 0.2, 20, z1 + 0.2, z2 - 0.2);
			}
		}

	}

	if (streetsOnZ[0] > 0.6) {
		for (int j = 0; j < streetsOnX.size() - 1; j++) {
			int x1 = streetsOnX[j];
			int x2 = streetsOnX[j + 1];
			int buildBuilding = prob[randomInt(0, prob.size() - 1)];
			if (buildBuilding == 1) {
				Building b = generateBuildingBetweenCoord(x1 + 0.2, x2 - 0.2, 0, streetsOnZ[0] - 0.2);
				buildings.push_back(b);
			}
			else {
				putGrass(x1 + 0.2, x2 - 0.2, 0, streetsOnZ[0] - 0.2);
			}
		}
	}

	if (streetsOnZ[streetsOnZ.size() - 1] < 19.4) {
		for (int j = 0; j < streetsOnX.size() - 1; j++) {
			int x1 = streetsOnX[j];
			int x2 = streetsOnX[j + 1];
			int buildBuilding = prob[randomInt(0, prob.size() - 1)];
			if (buildBuilding == 1) {
				Building b = generateBuildingBetweenCoord(x1 + 0.2, x2 - 0.2, streetsOnZ[streetsOnZ.size() - 1] + 0.2, 20);
				buildings.push_back(b);
			}
			else {
				putGrass(x1 + 0.2, x2 - 0.2, streetsOnZ[streetsOnZ.size() - 1] + 0.2, 20);
			}
		}
	}


	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i].baseHeight < 2) {
			int textureNumber = randomInt(1, 6);
			textures.push_back(std::to_string(textureNumber));
		}
		else {
			int textureNumber = randomInt(7, 12);
			textures.push_back(std::to_string(textureNumber));
		}
	}

	for (int i = 0; i < buildings.size(); i++) {
		if (buildings[i].baseHeight < 2) {
			int randomFloorNo = randomInt(0, 1);
			buildings[i].floorNo = randomFloorNo;
		}
		if (buildings[i].baseHeight < 1.5) {
			int randomFloorNo = randomInt(1,1);
			buildings[i].floorNo = randomFloorNo;
		}
	}
}

void CityView::renderBuildings()
{
	for (int i = 0; i < buildings.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		RenderSimpleMesh(buildings[i].buildingBase.first, shaders["ShaderTema3"], modelMatrix, mapTextures["building" + textures[i]]);
		RenderSimpleMesh(buildings[i].buildingBase.second, shaders["ShaderTema3"], modelMatrix, mapTextures["roofTexture"]);
		std::vector<glm::vec3> scallingFact = { glm::vec3(0.5, 0.25, 0.5), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.3, 0.2, 0.3) };
		for (int h = 0; h < buildings[i].floorNo; h++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			glm::vec3 scaleFact = buildings[i].baseHeight > 1 ? scallingFact[0] : scallingFact[1];
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, buildings[i].baseHeight, 0));
			modelMatrix = glm::scale(modelMatrix, scaleFact);
			modelMatrix = glm::translate(modelMatrix, buildings[i].center);

			RenderSimpleMesh(buildings[i].buildingBase.first, shaders["ShaderTema3"], modelMatrix, mapTextures["building" + textures[i]]);
			RenderSimpleMesh(buildings[i].buildingBase.second, shaders["ShaderTema3"], modelMatrix, mapTextures["roofTexture"]);
		}
	}
}

void CityView::putGrass(float x1, float x2, float z1, float z2)
{
	{
		glm::vec3 center = glm::vec3(x1 + fabs(x2 - x1) / 2.0f, 0.001, z1 + fabs(z2 - z1) / 2.0f);
		int decorationNo = randomInt(1, 2);
		if (decorationNo != 3) {
			Mesh* mesh = Objects::CreateRectangle("decoration", center, fabs(x2 - x1), fabs(z2 - z1), glm::vec2(5 * ceil(fabs(x2 - x1) / fabs(z2 - z1)), 5 * ceil(fabs(z2 - z1) / fabs(x2 - x1))));
			Decoration d = Decoration(mesh, "decoration" + std::to_string(decorationNo), x1, x2, z1, z2);
			decorations.push_back(d);
		}
		else {
			Decoration d = Decoration(meshes["decoration3"], "decoration" + std::to_string(decorationNo), x1, x2, z1, z2);
			decorations.push_back(d);
		}
	}
}



void CityView::renderDecorations()
{
	for (int i = 0; i < decorations.size(); i++) {
		if (decorations[i].texture == "decorations3") {
			float x1 = decorations[i].x1;
			float x2 = decorations[i].x1;
			float z1 = decorations[i].z1;
			float z2 = decorations[i].z2;
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(x1 + (x2 - x1) / 2.0, 0, x1 + (z2 - z1) / 2.0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2, 0.2, 0.2));
			glUseProgram(shaders["Simple"]->program);

			// Bind model matrix
			GLint loc_model_matrix = glGetUniformLocation(shaders["Simple"]->program, "Model");
			glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			// Bind view matrix
			glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
			int loc_view_matrix = glGetUniformLocation(shaders["Simple"]->program, "View");
			glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

			// Bind projection matrix
			glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
			int loc_projection_matrix = glGetUniformLocation(shaders["Simple"]->program, "Projection");
			glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			meshes["decoration3"]->Render();
		} else {
			int decorationNo = randomInt(1, 2);
			RenderSimpleMesh(decorations[i].mesh, shaders["ShaderTema3"], glm::mat4(1), mapTextures[decorations[i].texture]);
		}
	}
}

void CityView::renderWalls()
{

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 2.5, 10));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 5, 28));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 0, 1));
	RenderSimpleMesh(meshes["skyLeft"], shaders["ShaderTema3"], modelMatrix, mapTextures["wall"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(24, 2.5, 10));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 5, 28));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 0, 1));
	RenderSimpleMesh(meshes["skyLeft"], shaders["ShaderTema3"], modelMatrix, mapTextures["wall"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 2.5, -4));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(5, 2, 28));
	RenderSimpleMesh(meshes["skyLeft"], shaders["ShaderTema3"], modelMatrix, mapTextures["wall"]);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 2.5, 24));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(5, 2, 28));
	RenderSimpleMesh(meshes["skyLeft"], shaders["ShaderTema3"], modelMatrix, mapTextures["wall"]);
}

void CityView::generateTrees() {
	int noTrees = randomInt(5, 15);
	for (int i = 0; i < noTrees; i++) {
		float randZ = randomFloat(-3, 23);
		float randX = randomFloat(-3, 0.3);
		float randScale = randomFloat(0.1, 0.2);
		trees.push_back(std::make_tuple(randX, randZ, randScale));
	}

	noTrees = randomInt(5, 15);
	for (int i = 0; i < noTrees; i++) {
		float randZ = randomFloat(-2.5, 0.3);
		float randX = randomFloat(-3, 23.5);
		float randScale = randomFloat(0.1, 0.2);
		trees.push_back(std::make_tuple(randX, randZ, randScale));
	}

	noTrees = randomInt(5, 15);
	for (int i = 0; i < noTrees; i++) {
		float randZ = randomFloat(20.3, 23.5);
		float randX = randomFloat(-3, 23.5);
		float randScale = randomFloat(0.1, 0.2);
		trees.push_back(std::make_tuple(randX, randZ, randScale));
	}

	noTrees = randomInt(5, 15);
	for (int i = 0; i < noTrees; i++) {
		float randZ = randomFloat(-3, 23);
		float randX = randomFloat(20.3, 23.5);
		float randScale = randomFloat(0.1, 0.2);
		trees.push_back(std::make_tuple(randX, randZ, randScale));
	}
}
void CityView::renderTrees()
{
	for (int i = 0; i < trees.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(std::get<0>(trees[i]), 0, std::get<1>(trees[i])));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(std::get<2>(trees[i]), std::get<2>(trees[i]), std::get<2>(trees[i])));
		glUseProgram(shaders["Simple"]->program);

		// Bind model matrix
		GLint loc_model_matrix = glGetUniformLocation(shaders["Simple"]->program, "Model");
		glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		// Bind view matrix
		glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
		int loc_view_matrix = glGetUniformLocation(shaders["Simple"]->program, "View");
		glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		// Bind projection matrix
		glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
		int loc_projection_matrix = glGetUniformLocation(shaders["Simple"]->program, "Projection");
		glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		meshes["decoration3"]->Render();
	}
}