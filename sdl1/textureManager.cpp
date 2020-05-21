#include "textureManager.h"

SDL_Texture* textureManager::loadTexture(std::string filePath, SDL_Renderer* renderTarget) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		printf("error loading png %s", SDL_GetError);
	else {
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			printf("error creating texture: %s", SDL_GetError());
	}
	//SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);
	return texture;
}

