#include "Camera.h"
#include <SDL.h>


Camera::Camera(int mapWidthIn, int mapHeightIn) {
	mapHeight = mapHeightIn;
	mapWidth = mapWidthIn;
	mapScrollSpeed = 1000.0f;
	windowMoveTolerance = 5;
	screenWidth = 1600;
	screenHeight = 800;
	fractionOfMap = 1.9f;
	cameraPos = { 0,0,int(screenWidth / fractionOfMap), int(screenHeight / fractionOfMap) };
	cameraWidth = screenWidth / fractionOfMap;
	cameraHeight = screenHeight / fractionOfMap;
	cameraX = 0;
	cameraY = 0;
}

void Camera::moveCamera(float deltaTime, int mouseX, int mouseY) {
	if (mouseX >= screenWidth - windowMoveTolerance) {
		if (cameraPos.x + cameraWidth < mapWidth) {
			cameraPos.x += mapScrollSpeed * deltaTime;
		}
	}
	if (mouseX <= 0 + windowMoveTolerance) {
		if (cameraPos.x > 0) {
			cameraPos.x -= mapScrollSpeed * deltaTime;
		}
	}
	if (mouseY >= screenHeight - windowMoveTolerance) {
		if (cameraPos.y + cameraHeight < mapHeight) {
			cameraPos.y += mapScrollSpeed * deltaTime;
		}
	}
	if (mouseY <= 0 + windowMoveTolerance) {
		if (cameraPos.y > 0) {
			cameraPos.y -= mapScrollSpeed * deltaTime;
		}
	}
}

void Camera::drawImage(SDL_Renderer* renderTarget, SDL_Texture* texture, int positionX, int positionY) {
	SDL_Rect positionToDraw = { (positionX-cameraPos.x*fractionOfMap), (positionY-cameraPos.y * fractionOfMap),NULL,NULL };

	SDL_QueryTexture(texture, NULL, NULL, &positionToDraw.w, &positionToDraw.h);
	positionToDraw.x = positionToDraw.x - positionToDraw.w / 2;
	positionToDraw.y = positionToDraw.y - positionToDraw.h / 2;

	SDL_RenderCopy(renderTarget, texture, NULL, &positionToDraw);


}

void Camera::drawMap(SDL_Renderer* renderTarget, SDL_Texture* mapTexture) {
	SDL_RenderCopy(renderTarget, mapTexture, &cameraPos, NULL);
}

int Camera::getClickX(int onScreenX) {
	return cameraPos.x * fractionOfMap + onScreenX;
}
int Camera::getClickY(int onScreenY) {
	return cameraPos.y * fractionOfMap + onScreenY;
}