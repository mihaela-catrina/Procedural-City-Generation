#include "SceneGame.h"

void SceneGame::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Bind projection matrix
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

void SceneGame::RenderCueSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	int locationT = glGetUniformLocation(shader->program, "Time");
	glUniform1f(locationT, cueTime);

	int locationAngle = glGetUniformLocation(shader->program, "AngularStepOY");
	glUniform1f(locationAngle, cue.angularStepOY);

	int locationSpeedState = glGetUniformLocation(shader->program, "Speed");
	glUniform1f(locationSpeedState, cueSpeed);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void SceneGame::drawFloor() {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= Tema2_3DTransform::Translate(0, 0, 0);
	modelMatrix *= Tema2_3DTransform::Scale(1,1,1);
	RenderSimpleMesh(meshes["floor"], shaders["ShaderTema2"], modelMatrix, mapTextures["floorTexture"]);
}


void SceneGame::drawTable() {

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Tema2_3DTransform::Translate(table.base.translateX, table.base.translateY, table.base.translateZ);
		modelMatrix *= Tema2_3DTransform::Scale(table.base.scaleX, table.base.scaleY, table.base.scaleZ);
		RenderSimpleMesh(meshes[BASE], shaders["ShaderTema2"], modelMatrix, mapTextures["wood"]);

		modelMatrix = glm::mat4(1);
		modelMatrix *= Tema2_3DTransform::Translate(table.plywood.translateX, table.plywood.translateY, table.plywood.translateZ);
		modelMatrix *= Tema2_3DTransform::Scale(table.plywood.scaleX, table.plywood.scaleY, table.plywood.scaleZ);
		RenderSimpleMesh(meshes[PLYWOOD], shaders["ShaderTema2"], modelMatrix, mapTextures["boardTexture"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.pocketCorner1.translateX, table.pocketCorner1.translateY, table.pocketCorner1.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.pocketCorner1.scaleX, table.pocketCorner1.scaleY, table.pocketCorner1.scaleZ));
		RenderSimpleMesh(meshes[POCKET_CORNER1], shaders["ShaderTema2"], modelMatrix, mapTextures["pocket"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.pocketCorner2.translateX, table.pocketCorner2.translateY, table.pocketCorner2.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.pocketCorner2.scaleX, table.pocketCorner2.scaleY, table.pocketCorner2.scaleZ));
		RenderSimpleMesh(meshes[POCKET_CORNER2], shaders["ShaderTema2"], modelMatrix, mapTextures["pocket"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.pocketCorner3.translateX, table.pocketCorner3.translateY, table.pocketCorner3.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.pocketCorner3.scaleX, table.pocketCorner3.scaleY, table.pocketCorner3.scaleZ));
		RenderSimpleMesh(meshes[POCKET_CORNER3], shaders["ShaderTema2"], modelMatrix, mapTextures["pocket"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.pocketCorner4.translateX, table.pocketCorner4.translateY, table.pocketCorner4.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.pocketCorner4.scaleX, table.pocketCorner4.scaleY, table.pocketCorner4.scaleZ));
		RenderSimpleMesh(meshes[POCKET_CORNER4], shaders["ShaderTema2"], modelMatrix, mapTextures["pocket"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.pocketLeft.translateX, table.pocketLeft.translateY, table.pocketLeft.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.pocketLeft.scaleX, table.pocketLeft.scaleY, table.pocketLeft.scaleZ));
		RenderSimpleMesh(meshes[POCKET_LEFT], shaders["ShaderTema2"], modelMatrix, mapTextures["pocket"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.pocketRight.translateX, table.pocketRight.translateY, table.pocketRight.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.pocketRight.scaleX, table.pocketRight.scaleY, table.pocketRight.scaleZ));
		RenderSimpleMesh(meshes[POCKET_LEFT], shaders["ShaderTema2"], modelMatrix, mapTextures["pocket"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.rightBoarder.translateX, table.rightBoarder.translateY, table.rightBoarder.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.rightBoarder.scaleX, table.rightBoarder.scaleY, table.rightBoarder.scaleZ));
		RenderSimpleMesh(meshes[RIGHT_BOARDER], shaders["ShaderTema2"], modelMatrix, mapTextures["wood"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.leftBoarder.translateX, table.leftBoarder.translateY, table.leftBoarder.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.leftBoarder.scaleX, table.leftBoarder.scaleY, table.leftBoarder.scaleZ));
		RenderSimpleMesh(meshes[LEFT_BORDER], shaders["ShaderTema2"], modelMatrix, mapTextures["wood"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.bottomBoarder.translateX, table.bottomBoarder.translateY, table.bottomBoarder.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.bottomBoarder.scaleX, table.bottomBoarder.scaleY, table.bottomBoarder.scaleZ));
		RenderSimpleMesh(meshes[BOTTOM_BOARDER], shaders["ShaderTema2"], modelMatrix, mapTextures["wood"]);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(table.topBoarder.translateX, table.topBoarder.translateY, table.topBoarder.translateZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(table.topBoarder.scaleX, table.topBoarder.scaleY, table.topBoarder.scaleZ));
		RenderSimpleMesh(meshes[TOP_BOARDER], shaders["ShaderTema2"], modelMatrix, mapTextures["wood"]);
}

void SceneGame::setInitialBallsPosition() {
	float posZ = (-1) * table.length / 2.0f + table.length / 4.0f - 0.2;
	float center = 0.0;
	float shiftZ = 0;
	float shiftX = 0;
	std::vector<int> array1 = { 1 };
	std::vector<int> array2 = { 9,2 };
	std::vector<int> array3 = { 10,8,3 };
	std::vector<int> array4 = { 11,7,14,4 };
	std::vector<int> array5 = { 5,13,15,6,12 };
	int i = 1;

	cueBall.setScallingFactors();
	cueBall.setTranslations(0.0f, table.heigh + cueBall.radius, table.length / 2.0f - table.length / 4.0f + 0.3);

	for (int i = 0; i < array1.size(); i++) {
		balls[array1[i]].setScallingFactors();
		balls[array1[i]].setTranslations(center + shiftX, table.heigh + cueBall.radius, posZ + shiftZ);
	}
	shiftZ += 2*cueBall.radius;
	shiftX -= cueBall.radius;
	for (int i = 0; i < array2.size(); i++) {
		balls[array2[i]].setScallingFactors();
		balls[array2[i]].setTranslations(center + shiftX + i * 2 * cueBall.radius, table.heigh + cueBall.radius, posZ + shiftZ);
	}

	shiftZ += 2*cueBall.radius;
	shiftX -= cueBall.radius;
	for (int i = 0; i < array3.size(); i++) {
		balls[array3[i]].setScallingFactors();
		balls[array3[i]].setTranslations(center + shiftX + i * 2 * cueBall.radius, table.heigh + cueBall.radius, posZ + shiftZ);
	}

	shiftZ += 2 * cueBall.radius;
	shiftX -= cueBall.radius;
	for (int i = 0; i < array4.size(); i++) {
		balls[array4[i]].setScallingFactors();
		balls[array4[i]].setTranslations(center + shiftX + i * 2 * cueBall.radius, table.heigh + cueBall.radius, posZ + shiftZ);
	}

	shiftZ += 2 * cueBall.radius;
	shiftX -= cueBall.radius;
	for (int i = 0; i < array5.size(); i++) {
		balls[array5[i]].setScallingFactors();
		balls[array5[i]].setTranslations(center + shiftX + i * 2 * cueBall.radius, table.heigh + cueBall.radius, posZ + shiftZ);
	}


}

void SceneGame::drawBalls() {
	int i = 1;
	for (i = 1; i <= noBalls; i++) {
		auto modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(balls[i].translateX, balls[i].translateY, balls[i].translateZ));
		modelMatrix = glm::rotate(modelMatrix, balls[i].angularStepOZ, glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, balls[i].angularStepOX, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(balls[i].scaleX, balls[i].scaleY, balls[i].scaleZ));
		RenderSimpleMesh(meshes[GAMEBALL], shaders["ShaderTema2"], modelMatrix, mapTextures["Ball" + std::to_string(i)]);
	}

	drawCueBall();
}

void SceneGame::drawCueBall() {
	if (glm::length(cueBall.velocity) > 0) {
		cueBall.orientation = cueBall.velocity;
	}
	auto modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(cueBall.translateX, cueBall.translateY, cueBall.translateZ));
	modelMatrix = glm::rotate(modelMatrix, cueBall.angularStepOZ, glm::vec3(0, 0, 1));
	modelMatrix = glm::rotate(modelMatrix, cueBall.angularStepOX, glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(cueBall.scaleX, cueBall.scaleY, cueBall.scaleZ));
	RenderSimpleMesh(meshes[GAMEBALL], shaders["ShaderTema2"], modelMatrix, mapTextures["BallCue"]);
}

void SceneGame::setCue()
{
	cue.setScallingFactors();
	float xTransl = cueBall.translateX;
	float yTransl = cueBall.radius + table.bottomBoarder.translateY + table.bottomBoarder.scaleY / 2.0f;
	float zTransl = cueBall.translateZ + cueBall.radius + cue.scaleZ / 2.0f;
	cue.setTranslations(xTransl, yTransl, zTransl);
	float angleOx = std::atan((table.bottomBoarder.scaleY - table.plywood.scaleY) / 2.0f) / (table.length / 2.0 - cueBall.translateZ);
	cue.setRotation(angleOx, 0, 0);
}

void SceneGame::drawCue() {
	cue.angularStepOY = cameraRotationAlongOy;
	float xTransl = cueBall.translateX + (cue.scaleZ / 2.0f + cueBall.radius) * sin(cue.angularStepOY);
	float yTransl = cueBall.radius + table.bottomBoarder.translateY + table.bottomBoarder.scaleY / 2.0f;
	float zTransl = cueBall.translateZ + (cueBall.radius + cue.scaleZ / 2.0f) * cos(cue.angularStepOY);
	cue.setTranslations(xTransl, yTransl, zTransl);

	auto modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(cue.translateX, cue.translateY, cue.translateZ));
	modelMatrix = glm::rotate(modelMatrix, cue.angularStepOY, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, -(float)cue.angularStepOX, glm::vec3(1, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(cue.scaleX, cue.scaleY, cue.scaleZ));
	if (charge == CHARGE) {
		cueTime++;
		if (cueTime == 100) cueTime = 2;
		RenderCueSimpleMesh(meshes["cue"], shaders["ShaderCueTema2"], modelMatrix, mapTextures["cue"]);
	} else if (charge == RELEASE) {
		cueTime -= 2;
		RenderCueSimpleMesh(meshes["cue"], shaders["ShaderCueTema2"], modelMatrix, mapTextures["cue"]);
		if (cueTime <= 0) {
			charge = HIDE;
			cue.setForce(timeAtRelease, cueSpeed);
		}
	} else if (charge == IDLE) {
		RenderSimpleMesh(meshes["cue"], shaders["ShaderTema2"], modelMatrix, mapTextures["cue"]);
	}
}


void SceneGame::strikeCueBall() {
	glm::vec3 cueVel = glm::vec3(cueBall.translateX, cueBall.translateY, cueBall.translateZ) -
					   glm::vec3(cue.translateX, cueBall.translateY, cue.translateZ);
	cueVel = glm::normalize(cueVel)*(float)(cue.force);
	cueBall.velocity = cueVel;
	gameState = UPDATING;
}

void SceneGame::updateCueBall() {
	if (charge == HIDE) {
		strikeCueBall();
		charge = WAIT;
	}
	float dt = 0.05;
	if (glm::length(cueBall.velocity) < 0.02)
		cueBall.velocity = glm::vec3(0, 0, 0);
	else {
		glm::vec3 acc = glm::normalize(cueBall.velocity)*-0.1f;
		cueBall.velocity = cueBall.velocity + acc * dt;
	}
	float rotateAngleOx = cueBall.velocity.z * 180 / (M_PI * cueBall.radius) / 10;
	float rotateAngleOz = cueBall.velocity.x * 180 / (M_PI * cueBall.radius) / 10;

	cueBall.angularStepOX += rotateAngleOx;
	cueBall.angularStepOZ += rotateAngleOz;

	auto position = glm::vec3(cueBall.translateX, cueBall.translateY, cueBall.translateZ) + cueBall.velocity * dt;
	cueBall.translateX = position.x;
	cueBall.translateY = position.y;
	cueBall.translateZ = position.z;
}

void SceneGame::updateBalls() {
	float dt = 0.1;
	for (int i = 1; i <= noBalls; ++i) {
		if (glm::length(balls[i].velocity) < 0.02)
			balls[i].velocity = glm::vec3(0, 0, 0);
		else {
			glm::vec3 acc = glm::normalize(balls[i].velocity)*-0.1f;
			balls[i].velocity = balls[i].velocity + acc * dt;
		}

		float rotateAngleOx = balls[i].velocity.z * 180 / (M_PI * balls[i].radius) / 50;
		float rotateAngleOz = balls[i].velocity.x * 180 / (M_PI * balls[i].radius) / 50;

		balls[i].angularStepOX += rotateAngleOx;
		balls[i].angularStepOZ += rotateAngleOz;

			auto position = glm::vec3(balls[i].translateX, balls[i].translateY, balls[i].translateZ) + balls[i].velocity * dt;
			balls[i].translateX = position.x;
			balls[i].translateY = position.y;
			balls[i].translateZ = position.z;
	}
}

void SceneGame::checkCollisions() {
	for (int i = 1; i <= noBalls; i++) {
		table.updateBallIfHitTable(&balls[i]);
	}
	table.updateBallIfHitTable(&cueBall);

	for (int i = 1; i <= noBalls; i++) {
		if (cueBall.collisionWithOtherBall(&balls[i])) {
			cueBall.updateBallsWhenHit(&balls[i]);
			if (players[currentPlayer].playerType == FULL_BALLS &&
				std::find(fullBalls.begin(), fullBalls.end(), i) == fullBalls.end()) {
				players[currentPlayer].faults++;
			}

			if (players[currentPlayer].playerType == EMPTY_BALLS &&
				std::find(emptyBall.begin(), emptyBall.end(), i) == emptyBall.end()) {
				players[currentPlayer].faults++;
			}
		}
	}

	for (int i = 1; i <= noBalls; i++) {
		for (int j = i + 1; j <= noBalls; j++) {
			if (balls[i].collisionWithOtherBall(&balls[j])) {
				balls[i].updateBallsWhenHit(&balls[j]);
			}
		}
	}
}

void SceneGame::checkInPockets() {
	for (int i = 1; i <= noBalls; i++) {
		for (int j = 0; j < 6; j++) {
			bool isInPockets = table.pockets[j]->checkBallInPocket(&balls[i]);
			if (isInPockets) {
				ballIn = true;
				if (firstBallIn == false) {
					firstBallIn = true;
					setPlayers(i);
					players[currentPlayer].ballsInserted++;
				}
				else {
					checkPlayerBalls(i);
				}
				table.pockets[j]->updateBallPositionInPocket(&balls[i]);
				break;
			}
		}
	}

	for (int j = 0; j < 6; j++) {
		bool isInPockets = table.pockets[j]->checkBallInPocket(&cueBall);
		if (isInPockets) {
			table.pockets[j]->updateBallPositionInPocket(&cueBall);
		}
	}

	if (cueBall.isInPocket) {
		if (cueBall.velocity != glm::vec3(0, 0, 0)) {
			return;
		}
		for (int i = 1; i <= noBalls; i++) {
			if (balls[i].velocity != glm::vec3(0, 0, 0)) {
				return;
			}
		}

		cueBall.setTranslations(0.0f, table.heigh + cueBall.radius, table.length / 2.0f - table.length / 4.0f + 0.3);
		cueBall.isInPocket = false;
		cueBall.velocity = glm::vec3(0, 0, 0);

		players[currentPlayer].faults++;
		ballIn = true;
		switchPlayer();
	}
}

bool SceneGame::areBallsStatic() {
	bool flag = true;
	for (int i = 1; i <= noBalls; i++) {
		if (balls[i].velocity != glm::vec3(0, 0, 0)) {
			flag = false;
			break;
		}
	}

	if (cueBall.velocity != glm::vec3(0, 0, 0)) {
		flag = false;
	}

	return flag;
}

void SceneGame::setPlayers(int i) {
	for (auto &x : fullBalls) {
		if (i == x) {
			players[currentPlayer].playerType = FULL_BALLS;
			switchPlayer();
			players[currentPlayer].playerType = EMPTY_BALLS;
			switchPlayer();
			break;
		}
	}

	for (auto &x : emptyBall) {
		if (i == x) {
			players[currentPlayer].playerType = EMPTY_BALLS;
			switchPlayer();
			players[currentPlayer].playerType = FULL_BALLS;
			switchPlayer();
			break;
		}
	}

	if (i == blackBall) {
		players[currentPlayer].playerType = LOSER;
	}
}

void SceneGame::switchPlayer() {
	if (currentPlayer == PLAYER_1) {
		currentPlayer = PLAYER_2;
	} else {
		currentPlayer = PLAYER_1;
	}
}

void SceneGame::checkPlayerBalls(int ballNo) {
	bool found = false;
	
	if (blackBall == ballNo) {
		players[currentPlayer].playerType = LOSER;
		return;
	}

	if (players[currentPlayer].playerType == FULL_BALLS) {
		for (auto &x : fullBalls) {
			if (ballNo == x) {
				found = true;
				players[currentPlayer].ballsInserted++;
			}
		}
		if (!found) {
			players[currentPlayer].faults++;
			switchPlayer();
		}
	} else if (players[currentPlayer].playerType == EMPTY_BALLS) {
		for (auto &x : emptyBall) {
			if (ballNo == x) {
				found = true;
				players[currentPlayer].ballsInserted++;
			}
		}
		if (!found) {
			players[currentPlayer].faults++;
			switchPlayer();
		}	
	}
}

void SceneGame::showStatus() {
	if (gameState == SLEEP && !printed) {
		printf("Player_1 : faults: %d, balls: %d\n", players[1].faults, players[1].ballsInserted);
		printf("Player_2 : faults: %d, balls: %d\n", players[2].faults, players[2].ballsInserted);
		printf("Next player: %d;\n\n", currentPlayer);
		printed = true;
	}
}