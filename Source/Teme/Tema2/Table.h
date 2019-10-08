#pragma once
#include "ObjectTema2.h"
#include <Component/SimpleScene.h>

#include "Pocket.h"
#include "Ball.h"

constexpr auto BASE = "base";
constexpr auto PLYWOOD = "plywood";
constexpr auto LEFT_BORDER = "leftBoarder";
constexpr auto RIGHT_BOARDER = "rightBoarder";
constexpr auto TOP_BOARDER = "topBoarder";
constexpr auto BOTTOM_BOARDER = "bottomBoarder";
constexpr auto POCKET_CORNER1 = "pocketCorner1";
constexpr auto POCKET_CORNER2 = "pocketCorner2";
constexpr auto POCKET_CORNER3 = "pocketCorner3";
constexpr auto POCKET_CORNER4 = "pocketCorner4";
constexpr auto POCKET_LEFT = "pocketLeft";
constexpr auto POCKET_RIGHT = "pocketRight";

class Table : public ObjectTema2, SimpleScene {
public:
	Table() :
		ObjectTema2(ObjectTypeTema2::TABLE) 
	{
		setScallingFactors();
		setTranslations();
		setRotations();
	};

	void createMeshes(std::unordered_map<std::string, Mesh*> &meshes);
	void createTextures(std::unordered_map<std::string, Texture2D*> &mapTextures);
	void setScallingFactors();
	void setTranslations();
	void setRotations();
	void setHeight();
	void setLength();
	void setWidth();

	bool ballCollisionWithLeftBoarder(Ball *ball);
	bool ballCollisionWithRightBoarder(Ball *ball);
	bool ballCollisionWithTopBoarder(Ball *ball);
	bool ballCollisionWithBottomBoarder(Ball *ball);

	void updateBallIfHitTable(Ball *ball);

public:
	float left, right, top, bottom;
	ObjectTema2 base;
	ObjectTema2 plywood;
	ObjectTema2 leftBoarder;
	ObjectTema2 rightBoarder;
	ObjectTema2 topBoarder;
	ObjectTema2 bottomBoarder;
	Pocket pocketCorner1;
	Pocket pocketCorner2;
	Pocket pocketCorner3;
	Pocket pocketCorner4;
	Pocket pocketRight;
	Pocket pocketLeft;

	Pocket* pockets[6];
};