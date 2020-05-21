#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>


class textureManager
{
private:
public: 
	static SDL_Texture* loadTexture(std::string filePath, SDL_Renderer* renderTarget);
};

