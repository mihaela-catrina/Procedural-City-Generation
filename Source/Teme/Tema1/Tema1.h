#pragma once

#include <Teme/Tema1/GameScene.h>

class Tema1 : public GameScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
protected:
	glm::mat3 modelMatrix;
	float ballAngle = 0;             // ball angle
	float timer = 3;                 // timer for weapon power
	bool fired = false;              // true if the weapon behaviour is on and player shot
	float width;
	float height;
};
