#pragma once
#include "ObjectTema2.h"
#include <Component/SimpleScene.h>

class Cue : public ObjectTema2, SimpleScene {
public:
	static void createMesh(std::unordered_map<std::string, Mesh*> &meshes);
	static void createTexture(std::unordered_map<std::string, Texture2D*> &mapTextures);
	void setScallingFactors();
	void setTranslations(float x, float y, float z);
	void setRotation(float ax, float ay, float az);

	void setForce(float cueTime, float speed);
	float force = 0;
};