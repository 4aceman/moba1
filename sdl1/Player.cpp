#include "Player.h"
#include<SDL_image.h>
#include <iostream>
#include "Camera.h"
#include "textureManager.h"
#include <math.h>



Player::Player(SDL_Renderer* renderTarget, std::string filePath) {
	texture = textureManager::loadTexture(filePath, renderTarget);
	h = 0;
	theta = 0;
	positionX = 600;
	positionY = 500;
	positionToMoveToX = positionX;
	positionToMoveToY = positionY;

	moveSpeed = 100;

	static int playerNumber = 0;
	playerNumber++;
	if (playerNumber == 1) {
		//controls for 1st champion
	}
}

Player::~Player() {
	SDL_DestroyTexture(texture);
}

void Player::Move(float newX, float newY) {
	positionToMoveToX = newX;
	positionToMoveToY = newY;
}

void Player::Update(float deltaTime) {
	//if (positionToMoveToX != positionX) {
	//	theta = tan((positionToMoveToY - positionY) / (positionToMoveToX - positionX));
	//	printf("%f", theta);
	//	positionX += moveSpeed * deltaTime * asin(theta);
	//	positionY += moveSpeed * deltaTime * acos(theta);
	//}
	//h = sqrt((positionToMoveToX - positionX, 2) + (positionToMoveToY - positionY, 2));
	//printf("%f \n", (positionToMoveToX - positionX) / h * moveSpeed);

	//positionX += (positionToMoveToX - positionX) / h*moveSpeed;
	//positionY += (positionToMoveToY - positionY) / h*moveSpeed;

	if (abs(positionToMoveToX - positionX) > 5 && abs(positionToMoveToY - positionY)>5) {
		theta = atan((positionToMoveToY - positionY) / (positionToMoveToX - positionX));
		if (positionX < positionToMoveToX) {
			positionX += moveSpeed * deltaTime * cos(theta);

		}
		else {
			positionX -= moveSpeed * deltaTime * cos(theta);
		}
		if (positionY < positionToMoveToY) {
			positionY += moveSpeed * deltaTime * cos(theta);

		}
		else {
			positionY -= moveSpeed * deltaTime * sin(theta);
		}
		printf("theta:%f, y:%f, x:%f \n", theta, moveSpeed * deltaTime * acos(theta), moveSpeed * deltaTime * asin(theta));
	}

	//if (positionX < positionToMoveToX-2) {
	//	positionX += deltaTime * moveSpeed;
	//}
	//else if (positionX > positionToMoveToX+2) {
	//	positionX -= deltaTime * moveSpeed;
	//}
	//if (positionY < positionToMoveToY - 2) {
	//	positionY += deltaTime * moveSpeed;
	//}
	//else if (positionY > positionToMoveToY+2) {
	//	positionY -= deltaTime * moveSpeed;
	//}
}

void Player::Draw(SDL_Renderer* renderTarget, Camera camera) {
	camera.drawImage(renderTarget, texture, positionX, positionY);
}

//void Player::Control() {
//
//}
