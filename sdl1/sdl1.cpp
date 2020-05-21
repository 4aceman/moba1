#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include "Player.h"
#include "Camera.h"
#include "textureManager.h"

bool initialiseParameters() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Video Initialisation Error: %s", SDL_GetError());
		return false;
	}
	int imgFlags = IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("img init error", IMG_GetError());
		return false;
	}
	if (TTF_Init() < 0) {
		printf("TTF Initialisation Error: %s", TTF_GetError());
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;

	int xMouse;
	int yMouse;
	int mapWidth;
	int mapHeight;


	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0;
	float fps = 0;

	const Uint8* keyState;


	int ScreenWidth = 1600;
	int ScreenHeight = 800;



	SDL_Texture* mapTexture = NULL;

	SDL_Renderer* renderTarget = NULL;
	SDL_Rect rectOfMap;
	SDL_Rect chatPosition;
	chatPosition.x = 10;
	chatPosition.y = 10;


	if (!initialiseParameters()) {
		return 1;
	}
	
	//CREATE WINDOW--------------------------------------
	window = SDL_CreateWindow("Moba game test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED);
	if (window == NULL) {
		printf("Window Creation Error:", SDL_GetError);
		return 1;
	}

	//CREATE RENDER TARGET---------------------------------
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

	//LOAD MAP IMAGE---------------------------------
	mapTexture = textureManager::loadTexture("assets/SROld.jpg", renderTarget);
	if (mapTexture == NULL) {
		printf("Image loading failed: %s", SDL_GetError());
		return 1;
	}
	SDL_QueryTexture(mapTexture, NULL, NULL, &mapWidth, &mapHeight);


	//CREATE CAMERA----------------
	Camera camera1(mapWidth, mapHeight);


	//CREATE VOLI PLAYER FROM CLASS--------------------
	Player player1(renderTarget, "assets/volibear.png");


	//LOAD FONT---------------------------------
	TTF_Font* font = TTF_OpenFont("assets/standard_font.ttf", 18);
	if (font == NULL) {
		printf("error loading font: %s", TTF_GetError());
		return 1;
	}
	SDL_Colour colour = { 144,77, 255,255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "test", colour);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	if (textSurface == NULL || textTexture == NULL) {
		printf("error loading font: %s", TTF_GetError());
		return 1;
	}
	SDL_FreeSurface(textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &chatPosition.w, &chatPosition.h);
	textSurface = NULL;


	//CREATE MAIN GAME LOOP-----------------------------------
	bool running = true;
	SDL_Event ev;
	while (running) {
		prevTime = SDL_GetTicks();
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				running = false;
				printf("Exiting game.");
			}
			else if (ev.type == SDL_MOUSEBUTTONDOWN) {
				if (ev.button.button == SDL_BUTTON_RIGHT) {
					xMouse = camera1.getClickX(ev.button.x);
					yMouse = camera1.getClickX(ev.button.y);
					player1.Move(camera1.getClickX(ev.button.x), camera1.getClickY(ev.button.y));
					//x = ev.button.x;
					//y = ev.button.y;
				}
			}
		}
		SDL_GetMouseState(&xMouse, &yMouse);
		camera1.moveCamera(deltaTime, xMouse, yMouse);
		SDL_RenderClear(renderTarget);
		//SDL_RenderCopy(renderTarget, mapTexture, &camera1.cameraPos, NULL);
		camera1.drawMap(renderTarget, mapTexture);
		SDL_RenderCopy(renderTarget, textTexture, NULL, &chatPosition);
		player1.Update(deltaTime);
		player1.Draw(renderTarget, camera1);
		SDL_RenderPresent(renderTarget);
		SDL_Delay(1000 / 60);
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;
		fps = 1.0f / deltaTime;
	}
	player1.~Player();
	SDL_DestroyTexture(mapTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyWindow(window);
	mapTexture = textTexture = nullptr;
	renderTarget = nullptr;
	window = nullptr;
	IMG_Quit();
	SDL_Quit();
	return 0;
}