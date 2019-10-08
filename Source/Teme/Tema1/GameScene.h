#pragma once
#include <Core/World.h>
#include <Component/SimpleScene.h>
#include <stack>
#include <deque>
#include <unordered_map>
#include "Wall.h"
#include "Brick.h"
#include "Ball.h"
#include "Platform.h"

typedef struct COLOR {
	float r;
	float g;
	float b;
}COLOR;

extern COLOR red;
extern COLOR green;
extern COLOR black;
extern COLOR brown;
extern COLOR coolblue;
extern COLOR silver;
extern COLOR yellow;
extern COLOR teal;
extern COLOR lblue;
extern COLOR white;

constexpr auto PI = 3.14159;

enum GameState {
	NORMAL,                                    // no power
	WEAPON_POWER,                              // weapon on
	NO_REFLECTION_ON_BRICK_COLLISION_POWER,    // no reflection with the bricks
	WIN                                        // success
};

namespace EngineComponents
{
	class Camera;
	class Transform;
}

class GameScene : public SimpleScene {
public:
	// functions used for walls rendering
	void createSceneWalls(glm::ivec2 sceneResolution);
	void drawSceneWalls();

	// functions used for bricks rendering
	void createBricks(glm::ivec2 sceneResolution);
	void drawSceneBricks(float deltaTimeSeconds);

	// functions used for ball rendering
	void createBall(glm::ivec2 sceneResolution);
	void drawBall(float deltaTimeSeconds);

	// functions used for platform rendering
	void createPlatform(glm::ivec2 sceneResolution);
	void drawPlatform();

	// functions used to create power array = draw lifes
	void createLifesArray(glm::ivec2 sceneResolution);
	void drawPower();

	// update ball state
	void updateBallPosition(float deltaTimeSeconds);
	void updateBallDirection(float objPosX, float objPosY, float width, float height);

	// check Collision : walls + bricks
	void checkCollision();

	// check ball - platform collision
	void checkTouchPlatform();

	// function to check ball - brick collision
	bool checkBallBrickCollision(int i, int j);

	// // function to powerUp - platform collision
	bool checkCollisonPowerUpPlatform(PowerUp P);

	// function to check ball - rectangle collision
	bool checkBallRectangularObjCollision(float posX, float posY, float width, float height);

	// function to update lifes and reset ball position
	void updatePowerAndRestart();

	// used to draw game over face
	void createGameOverFace();
	void drawGameOverFace();

	// used to draw success sign
	void createCheckSign();
	void drawCheckSign();

	// verify if the player won
	void verifySuccess();

	// settersfor the power behaviours
	void setWeaponBehaviour();
	void setNoReflectionBehaviour();

	// functions used for the WEAPON power (create, draw and reset bullets stack)
	void createBullets();
	void drawBullets(float deltaTime, bool fired);
	void resetBullets();

	// reinitialize game (when the player won or when number of lifes <= 0
	void Reinitialize();                                

	int lifes = 3;										// number of lifes
	float timer = 2;									// timer for the NO_REFLECTION POWER
	bool ballOnThePlatform = true;                      // true if ball is on the platform
	bool success = false;                               // true if the player won the game
	GameState gameState = GameState::NORMAL;            // game state

protected:
	// constants used in game
	static const int noBricksPerLine = 12;
	static const int noBricksPerColon = 10;
	static const int wallSize = 25;
	static const int offsetOnX = 80;
	static const int offsetOnYUp = 50;
	static const int offsetOnYDown = 200;
	static const int spaceBetweenBricks = 15;
	static const int platformLength = 300;
	static const int platformHeight = 10;
	static const int ballRadius = 10;
	static const int platformHeightOnScene = 30;
	static const int bulletsNumber = 100;
	glm::ivec2 brickSize;								// brick width and height

	std::vector<Wall> walls;                            // walls	  
	std::vector<std::vector<Brick>> bricks;             // bricks
	std::unordered_map < std::string, Ball> bullets;    // all available bullets
	std::stack<Ball> bulletsStack;                      // bullets that can be used
	std::unordered_map<std::string, bool> usedBullets;  // used bullets whena WEPON power is on
	Ball ball;										    // ball obj
	Platform platform;									// platform object
	std::vector<Ball> power;							// object retaining lifes (=power)  
	std::vector<Brick> checkSign;						// object to be rendered if the game is won                
	std::pair<double, double> sResolution;				// scene Resolution
};
