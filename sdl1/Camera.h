#pragma once
#include <SDL.h>

class Camera
{
private:
	int mapScrollSpeed;
	int windowMoveTolerance;
	int screenWidth;
	int screenHeight;
	float fractionOfMap;
	int mapHeight;
	int mapWidth;
public:
	Camera(int mapWidthIn, int mapHeightIn);
	int cameraX;
	int cameraY;
	int cameraWidth;
	int cameraHeight;
	SDL_Rect cameraPos;
	void moveCamera(float deltaTime, int mouseX, int mouseY);
	void drawImage(SDL_Renderer* renderTarget, SDL_Texture* texture, int positionX, int positionY);
	void drawMap(SDL_Renderer* renderTarget, SDL_Texture* mapTexture);
	int getClickX(int onScreenX);
	int getClickY(int onScreenY);
};

