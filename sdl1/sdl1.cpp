#include<SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Surface* windowSurface = NULL;
	SDL_Surface* imageSurface = NULL;
	int ScreenWidth = 640;
	int ScreenHeight = 480;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("Video Initialisation Error:", SDL_GetError());
	else {
		window = SDL_CreateWindow("Moba game test", NULL, NULL, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL)
			printf("Window Creation Error:", SDL_GetError);
		else {
			windowSurface = SDL_GetWindowSurface(window);
			imageSurface = SDL_LoadBMP("assets/hello_world.bmp");
			if (imageSurface == NULL)
				printf("Image loading failed: ", SDL_GetError());
			else {
				SDL_BlitSurface(imageSurface,NULL, windowSurface, NULL);
				SDL_UpdateWindowSurface(window);
				SDL_Delay(2000);
			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}