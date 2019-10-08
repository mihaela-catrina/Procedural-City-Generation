#pragma once
#include <iostream>
#include <Core/Engine.h>
#include "3DTransform.h"



enum ObjectTypeTema2 {
	BALL,
	TABLE,
	POCKET,
};

class ObjectTema2 {
private:
	ObjectTypeTema2 type;
public:

	float positionX = 0;
	float positionY = 0;
	float positionZ = 0;
	float width = 0;
	float heigh = 0;
	float length = 0;
	float translateX, translateY, translateZ;
	float scaleX = 1, scaleY = 1, scaleZ = 1;
	float angularStepOX, angularStepOY, angularStepOZ;
	std::string name;
	ObjectTypeTema2 getObjectType() {
		return type;
	}

	ObjectTema2() {}

	ObjectTema2(ObjectTypeTema2 type) {
		this->type = type;
	}
};