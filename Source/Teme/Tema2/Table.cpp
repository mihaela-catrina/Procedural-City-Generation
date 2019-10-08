#include "Table.h"

void Table::createMeshes(std::unordered_map<std::string, Mesh*> &meshes) {
	Mesh* baseMesh = new Mesh(BASE);
	baseMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[baseMesh->GetMeshID()] = baseMesh;

	Mesh* plyWoodMesh = new Mesh(PLYWOOD);
	plyWoodMesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[plyWoodMesh->GetMeshID()] = plyWoodMesh;

	Mesh* leftBoarder = new Mesh(LEFT_BORDER);
	leftBoarder->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[leftBoarder->GetMeshID()] = leftBoarder;

	Mesh* rightBoarder = new Mesh(RIGHT_BOARDER);
	rightBoarder->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[rightBoarder->GetMeshID()] = rightBoarder;

	Mesh* topBoarder = new Mesh(TOP_BOARDER);
	topBoarder->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[topBoarder->GetMeshID()] = topBoarder;

	Mesh* bottomBoarder = new Mesh(BOTTOM_BOARDER);
	bottomBoarder->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[bottomBoarder->GetMeshID()] = bottomBoarder;


	Mesh* pocketCorner1 = new Mesh(POCKET_CORNER1);
	pocketCorner1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[pocketCorner1->GetMeshID()] = pocketCorner1;

	Mesh* pocketCorner2 = new Mesh(POCKET_CORNER2);
	pocketCorner2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[pocketCorner2->GetMeshID()] = pocketCorner2;

	Mesh* pocketCorner3 = new Mesh(POCKET_CORNER3);
	pocketCorner3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[pocketCorner3->GetMeshID()] = pocketCorner3;

	Mesh* pocketCorner4 = new Mesh(POCKET_CORNER4);
	pocketCorner4->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[pocketCorner4->GetMeshID()] = pocketCorner4;

	Mesh* pocketLeft = new Mesh(POCKET_LEFT);
	pocketLeft->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[pocketLeft->GetMeshID()] = pocketLeft;

	Mesh* pocketRight = new Mesh(POCKET_RIGHT);
	pocketRight->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
	meshes[pocketRight->GetMeshID()] = pocketRight;
}

void Table::createTextures(std::unordered_map<std::string, Texture2D*> &mapTextures) {
	const std::string textureLoc = "Source/Teme/Tema2/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "floor.jpg").c_str(), GL_REPEAT);
		mapTextures["wood"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "2gr2.jpg").c_str(), GL_REPEAT);
		mapTextures["boardTexture"] = texture;

		texture = new Texture2D();
		texture->Load2D((textureLoc + "Dirtbl.jpg").c_str(), GL_REPEAT);
		mapTextures["pocket"] = texture;
	}
}

void Table::setScallingFactors()
{
	base.scaleX = 2.52;
	base.scaleY = 0.6;
	base.scaleZ = 5.5;

	plywood.scaleX = 3.0f;
	plywood.scaleY = 0.2f;
	plywood.scaleZ = 6.0f;

	pocketCorner1.scaleX = 0.4f;
	pocketCorner1.scaleY = 0.1f;
	pocketCorner1.scaleZ = 0.4f;
	pocketCorner1.radius = pocketCorner1.scaleX;
	pockets[0] = &pocketCorner1;

	pocketCorner2.scaleX = 0.4f;
	pocketCorner2.scaleY = 0.1f;
	pocketCorner2.scaleZ = 0.4f;
	pocketCorner2.radius = pocketCorner2.scaleX;
	pockets[1] = &pocketCorner2;

	pocketCorner3.scaleX = 0.4f;
	pocketCorner3.scaleY = 0.1f;
	pocketCorner3.scaleZ = 0.4f;
	pocketCorner3.radius = pocketCorner3.scaleX;
	pockets[2] = &pocketCorner3;

	pocketCorner4.scaleX = 0.4f;
	pocketCorner4.scaleY = 0.1f;
	pocketCorner4.scaleZ = 0.4f;
	pocketCorner4.radius = pocketCorner4.scaleX;
	pockets[3] = &pocketCorner4;

	pocketLeft.scaleX = 0.4f;
	pocketLeft.scaleY = 0.1f;
	pocketLeft.scaleZ = 0.4f;
	pocketLeft.radius = pocketLeft.scaleX;
	pockets[4] = &pocketLeft;

	pocketRight.scaleX = 0.4f;
	pocketRight.scaleY = 0.1f;
	pocketRight.scaleZ = 0.4f;
	pocketRight.radius = pocketRight.scaleX;
	pockets[5] = &pocketRight;

	rightBoarder.scaleX = 0.3f;
	rightBoarder.scaleY = 0.3f;
	rightBoarder.scaleZ = 6.1f;

	leftBoarder.scaleX = 0.3f;
	leftBoarder.scaleY = 0.3f;
	leftBoarder.scaleZ = 6.1f;

	bottomBoarder.scaleX = plywood.scaleX + rightBoarder.scaleX + 0.001;
	bottomBoarder.scaleY = rightBoarder.scaleY + 0.001;
	bottomBoarder.scaleZ = rightBoarder.scaleX;

	topBoarder.scaleX = bottomBoarder.scaleX;
	topBoarder.scaleY = bottomBoarder.scaleY;
	topBoarder.scaleZ = bottomBoarder.scaleZ;
}

void Table::setTranslations()
{
	base.translateX = 0.0f;
	base.translateY = base.scaleY / 2.0f;
	base.translateZ = 0.0f;

	plywood.translateX = 0.0f;
	plywood.translateY = base.scaleY + plywood.scaleY / 2.0f;
	plywood.translateZ = 0.0f;

	rightBoarder.translateX = plywood.scaleX / 2.0f;
	rightBoarder.translateY = plywood.translateY;
	rightBoarder.translateZ = 0.0f;

	bottomBoarder.translateX = plywood.translateX;
	bottomBoarder.translateY = plywood.translateY;
	bottomBoarder.translateZ = plywood.scaleZ / 2.0f;

	leftBoarder.translateX = (-1)*plywood.scaleX / 2.0f;
	leftBoarder.translateY = plywood.translateY;
	leftBoarder.translateZ = rightBoarder.translateZ;

	topBoarder.translateX = plywood.translateX;
	topBoarder.translateY = plywood.translateY;
	topBoarder.translateZ = (-1)*plywood.scaleZ / 2.0f;

	pocketCorner1.translateX = plywood.scaleX / 2.0f - rightBoarder.scaleX / 2.0f;
	pocketCorner1.translateY = plywood.translateY + 0.1;
	pocketCorner1.translateZ = plywood.scaleZ / 2.0f - rightBoarder.scaleX / 2.0f;

	pocketCorner2.translateX = (-1) * plywood.scaleX / 2.0f + rightBoarder.scaleX / 2.0f;;
	pocketCorner2.translateY = plywood.translateY + 0.1;
	pocketCorner2.translateZ = plywood.scaleZ / 2.0f - rightBoarder.scaleX / 2.0f;


	pocketCorner3.translateX = plywood.scaleX / 2.0f - rightBoarder.scaleX / 2.0f;
	pocketCorner3.translateY = plywood.translateY + 0.1;
	pocketCorner3.translateZ = (-1)*plywood.scaleZ / 2.0f + rightBoarder.scaleX / 2.0f;

	pocketCorner4.translateX = (-1) * plywood.scaleX / 2.0f + rightBoarder.scaleX / 2.0f;;
	pocketCorner4.translateY = plywood.translateY + 0.1;
	pocketCorner4.translateZ = (-1)*plywood.scaleZ / 2.0f + rightBoarder.scaleX / 2.0f;

	pocketLeft.translateX = (-1) * plywood.scaleX / 2.0f + pocketLeft.scaleX / 2.0 - 0.1;
	pocketLeft.translateY = pocketCorner3.translateY;
	pocketLeft.translateZ = 0.0f;

	pocketRight.translateX = plywood.scaleX / 2.0f - pocketLeft.scaleX / 2.0 + 0.1;
	pocketRight.translateY = pocketCorner3.translateY;
	pocketRight.translateZ = 0.0f;
}

void Table::setRotations()
{
	pocketCorner1.angularStepOZ = 3.14519 / 2.0f;
}

void Table::setHeight() {
	heigh = plywood.translateY + plywood.scaleY / 2.0f;
}

void Table::setLength() {
	length = plywood.scaleZ - bottomBoarder.scaleZ;
}

void Table::setWidth() {
	width = plywood.scaleX - rightBoarder.scaleX;
}

bool Table::ballCollisionWithLeftBoarder(Ball *ball) {
	if (ball->translateX < (this->leftBoarder.translateX + this->leftBoarder.scaleX / 2.0f + ball->radius))
		return true;
	else
		return false;
}

bool Table::ballCollisionWithRightBoarder(Ball *ball) {
	if (ball->translateX > (this->rightBoarder.translateX - this->leftBoarder.scaleX / 2.0f - ball->radius))
		return true;
	else
		return false;
}

bool Table::ballCollisionWithTopBoarder(Ball *ball) {
	if (ball->translateZ < (this->topBoarder.translateZ + this->topBoarder.scaleZ / 2.0f + ball->radius))
		return true;
	else
		return false;
}

bool Table::ballCollisionWithBottomBoarder(Ball *ball) {
	if (ball->translateZ > (this->bottomBoarder.translateZ - this->bottomBoarder.scaleZ / 2.0f - ball->radius))
		return true;
	else
		return false;
}

void Table::updateBallIfHitTable(Ball *ball) {
	if (ballCollisionWithLeftBoarder(ball)) {
		ball->velocity.x = -ball->velocity.x;
		ball->translateX = this->leftBoarder.translateX + this->leftBoarder.scaleX / 2.0f + ball->radius;
	} else if (ballCollisionWithRightBoarder(ball)) {
		ball->velocity.x = -ball->velocity.x;
		ball->translateX = this->rightBoarder.translateX - this->leftBoarder.scaleX / 2.0f - ball->radius;
	}

	if (ballCollisionWithTopBoarder(ball)) {
		ball->velocity.z = -ball->velocity.z;
		ball->translateZ = this->topBoarder.translateZ + this->topBoarder.scaleZ / 2.0f + ball->radius;
	} else if (ballCollisionWithBottomBoarder(ball)) {
		ball->velocity.z = -ball->velocity.z;
		ball->translateZ = this->bottomBoarder.translateZ - this->bottomBoarder.scaleZ / 2.0f - ball->radius;
	}
}
