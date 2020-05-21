#pragma once

#include<SDL.h>
#include<string>
#include"Camera.h"
#include"textureManager.h"

class Player
{
private: 
	SDL_Texture* texture;
	float moveSpeed;
	float positionX;
	float positionToMoveToX;
	float positionY;
	float positionToMoveToY;
	float h;
	float theta;

public:
	Player(SDL_Renderer* renderTarget, std::string filePath);
	~Player();
	void Move(float newX, float newY);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderTarget, Camera camera);

};

