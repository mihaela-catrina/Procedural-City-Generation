 #pragma once
#include "ObjectIn2D.h"

#include <Core/Engine.h>

Mesh* ObjectIn2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* ObjectIn2D::CreateCircle(std::string name, float _radius, glm::vec3 color, float step, bool fill)
{
	int indicesNumber = 1;
	double degrees = 2 * 3.14159;
	std::vector<VertexFormat> vertices;
	{
		float x1, y1, x2, y2;
		double radius = _radius;
		vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
		x1 = radius, y1 = 0;
		vertices.push_back(VertexFormat(glm::vec3(x1, y1, 0), color));
		for (float angle = 0.0f; angle <= degrees; angle += step) {
			x2 = cos(angle)*radius;
			y2 = sin(angle)*radius;
			auto v = VertexFormat(glm::vec3(x2, y2, 0), color);
			vertices.push_back(v);
			indicesNumber++;
		}
	}

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices;

	if (!fill) {
		for (int i = 0; i <= indicesNumber; i++) {
			indices.push_back(i);
		}
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(1);
		indices.push_back(0);
		// draw 2 triangles. Add the remaining 2 indices
		for (int i = 2; i <= indicesNumber; i++) {
			indices.push_back(i);
			indices.push_back(i);
			indices.push_back(0);	
		}
		indices.push_back(1);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh * ObjectIn2D::CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color, bool fill)
{
	return CreateRectangle("platform", glm::vec3(0, 0, 0), height, width, color, true);
}

Mesh * ObjectIn2D::CreateSemicircle(std::string name, float radius, glm::vec3 color, float step)
{
	int indicesNumber = 0;
	double degrees = 3.14159;
	std::vector<VertexFormat> vertices;
	{
		float x1, y1, x2, y2;
		double radius = 15;
		x1 = (-1)*radius, y1 = 0;
		vertices.push_back(VertexFormat(glm::vec3(x1, y1, 0), color));
		for (float angle = 0.0f; angle <= degrees; angle += step) {
			x2 = cos(angle)*radius;
			y2 = sin(angle)*radius;
			auto v = VertexFormat(glm::vec3(x2, y2, 0), color);
			vertices.push_back(v);
			indicesNumber++;
		}
	}

	Mesh* semicircle = new Mesh(name);
	std::vector<unsigned short> indices;

	for (int i = 0; i <= indicesNumber; i++) {
		indices.push_back(i);
	}
	semicircle->SetDrawMode(GL_LINE_STRIP);

	semicircle->InitFromData(vertices, indices);
	return semicircle;
}
