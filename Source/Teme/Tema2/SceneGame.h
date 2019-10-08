#pragma once
#include <Core/World.h>
#include <Component/SimpleScene.h>
#include <unordered_map>
#include <vector>

#include "Table.h"
#include "Ball.h"
#include "ObjectTema2.h"
#include "Camera.h"
#include "Cue.h"

#define PLAYER_1 1
#define PLAYER_2 2

enum GameState {
	START,
	CUE_ON_SCENE_START,
	CUE_ON_SCENE,
	CUE_BALL_JUST_HIT,
	CHARGE_STATE,
	SLEEP,
	UPDATING
};

enum CueState {
	IDLE,
	CHARGE,
	RELEASE,
	HIDE,
	WAIT
};

enum PlayerBalls {
	NONE,
	FULL_BALLS,
	EMPTY_BALLS,
	LOSER
};

struct Player {
	PlayerBalls playerType;
	int playerNo;
	int faults = 0;
	int ballsInserted = 0;
};

class SceneGame : public SimpleScene {
public:
	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1);
	void RenderCueSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1);

	void drawTable();
	void drawBalls();
	void drawCueBall();
	void updateCueBall();
	void updateBalls();
	void drawCue();
	void setInitialBallsPosition();
	void setCue();

	void strikeCueBall();

	void checkCollisions();
	void checkInPockets();

	void drawFloor();

	void switchPlayer();
	void setPlayers(int i);
	void checkPlayerBalls(int ballNo);

	void showStatus();

	bool areBallsStatic();

public:
	static const int noBalls = 15;
	std::unordered_map<std::string, Texture2D*> mapTextures;
	Table table;
	Ball balls[noBalls + 1];
	Ball cueBall;
	Cue cue;

	Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	float cameraRotationAlongOx = 0;
	float cameraRotationAlongOy = 0;
	GameState gameState = START;
	CueState charge = IDLE;

	float cueTime = 0;
	const float cueSpeed = 0.01;
	float timeAtRelease = 0;
	bool allVelocitiesZero = true;

	bool firstBallIn = false;
	bool ballIn = false;

	Player players[3];
	
	std::vector<int> fullBalls = { 1, 2, 3, 4, 5, 6, 7 };
	std::vector<int> emptyBall = { 9, 10, 11, 12, 13, 14, 15 };
	int blackBall = 8;
	int currentPlayer = PLAYER_1;
	bool printed = false;

};