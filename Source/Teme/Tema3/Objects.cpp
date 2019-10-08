#pragma once
#include "Objects.h"
#include <vector>

#include <Core/Engine.h>

Mesh* Objects::CreateRectangle(std::string name, glm::vec3 center, float sizeX, float sizeZ, glm::vec2 textCoord)
{
	std::vector<glm::vec3> vertices = 
	{
		glm::vec3(center.x + sizeX / 2.0f,   center.y, center.z - sizeZ / 2.0f),	// Top Right
		glm::vec3(center.x + sizeX / 2.0f, center.y, center.z + sizeZ / 2.0f),	// Bottom Right
		glm::vec3(center.x - sizeX / 2.0f, center.y, center.z + sizeZ / 2.0f),	// Bottom Left
		glm::vec3(center.x - sizeX / 2.0f,  center.y, center.z - sizeZ / 2.0f),	// Top Left
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0)
	};

	// TODO : Complete texture coordinates for the square
	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(textCoord.x, textCoord.y),
		glm::vec2(textCoord.x, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, textCoord.y)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, normals, textureCoords, indices);
	return mesh;
}

std::pair<Mesh*, Mesh*> Objects::CreateBuilding(std::string name, float _radius, glm::vec3 center, int faces, float height)
{
	if (faces % 2 == 1)
		faces -= 1;
	int indicesNumber = 0;
	double degrees = 2 * 3.14159;
	float step = degrees / (float)faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> roofVertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> roofNormals;
	std::vector<glm::vec2> textureCoords;

	//create vertices and compute normals
	{
		float x1, y1, x2, y2;
		double radius = _radius;
		roofVertices.push_back(center + glm::vec3(0, height, 0));
		roofNormals.push_back(glm::vec3(0, 0, 0));
		x1 = radius, y1 = 0;
		for (float angle = 0.0f; angle <= degrees; angle += step) {
			x2 = cos(angle)*radius;
			y2 = sin(angle)*radius;
			auto v = glm::vec3(x2, 0, y2) + center;
			vertices.push_back(v);
			normals.push_back(glm::normalize(glm::cross(v, center)));
			vertices.push_back(v + glm::vec3(0, height, 0));
			normals.push_back(glm::normalize(glm::cross(v + glm::vec3(0, height, 0), center)));

			roofVertices.push_back(v + glm::vec3(0, height, 0));
			roofNormals.push_back(glm::normalize(glm::cross(v + glm::vec3(0, height, 0), center)));
			indicesNumber += 2;
		}
	}

	// create indices array
	std::vector<unsigned short> indices;
	{
		int vx = 3;
		while (vx < indicesNumber) {
			indices.push_back(vx - 3);
			indices.push_back(vx);
			indices.push_back(vx - 2);
			indices.push_back(vx - 3);
			indices.push_back(vx - 1);
			indices.push_back(vx);
			vx += 2;
		}

		indices.push_back(indicesNumber - 2);
		indices.push_back(indicesNumber - 1);
		indices.push_back(0);
		indices.push_back(indicesNumber - 1);
		indices.push_back(1);
		indices.push_back(0);
	}

	//texture coordinates
	{
		bool left = true;
		int i = 0;
		while (i < indicesNumber / 2) {
			if (left == true) {
				textureCoords.push_back(glm::vec2(0, 2));
				textureCoords.push_back(glm::vec2(0, 0));
				left = false;
			}
			else {
				textureCoords.push_back(glm::vec2(1, 2));
				textureCoords.push_back(glm::vec2(1, 0));
				left = true;
			}
			i++;
		}
	}

	//create mesh for the walls
	Mesh* walls = new Mesh(name);
	walls->InitFromData(vertices, normals, textureCoords, indices);
	
	// create roof mesh
	Mesh* roof = new Mesh(name + "roof");
	{
		std::vector<glm::vec3> normals;
		std::vector<unsigned short> indices;
		std::vector<glm::vec2> textureCoords;

		indices.push_back(1);
		indices.push_back(0);
		// draw 2 triangles. Add the remaining 2 indices
		for (int i = 2; i <= indicesNumber / 2; i++) {
			indices.push_back(i);
			indices.push_back(i);
			indices.push_back(0);
		}
		indices.push_back(1);

		int j = 0;
		textureCoords.push_back(glm::vec2(0, 0));
		for (int i = 0; i <= indicesNumber / 2; i++) {
			if(j == 0)
				textureCoords.push_back(glm::vec2(0, 1));
			if (j == 1)
				textureCoords.push_back(glm::vec2(1, 1));
			j++;
			if (j == 2)
				j = 0;
		}
		roof->InitFromData(roofVertices, roofNormals, textureCoords, indices);
	}

	return std::make_pair(walls, roof);
}