#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")

#include "defines.h"
#include "utils.h"


#define IMG_red   "C:\\Users\\morit\\source\\repos\\SDL2_OpenGL_Test5\\SDL2_OpenGL_Test5\\DVD-Video-Red.png"
#define IMG_green "C:\\Users\\morit\\source\\repos\\SDL2_OpenGL_Test5\\SDL2_OpenGL_Test5\\DVD-Video-Green.png"
#define IMG_blue  "C:\\Users\\morit\\source\\repos\\SDL2_OpenGL_Test5\\SDL2_OpenGL_Test5\\DVD-Video-Blue.png"


int main(int argc, char* argv[]) {
	SDL_Window* window = nullptr;
	SDL_Surface* image[3];
	SDL_Renderer* renderer = nullptr;
	SDL_DisplayMode dm;

	// Initializing SDL_image and SDL2 and handle error if given
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		std::cerr << "IMG_Init: Failed to init required jpg and png support!\n"
				  << "IMG_Init: " << IMG_GetError() << std::endl;
		return 1;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING))
		printe(PRINTE_ERROR_SDL2, SDL_GetError(), true);


	window = SDL_CreateWindow("DVD-Video", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	image[0] = IMG_Load(IMG_red);
	image[1] = IMG_Load(IMG_green);
	image[2] = IMG_Load(IMG_blue);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(window), &dm))
		printe(PRINTE_ERROR_SDL2, SDL_GetError(), true);
	if (!window || !image[0] || !image[1] || !image[2] || !renderer)
		printe(PRINTE_ERROR_SDL2, SDL_GetError(), true);


	SDL_FRect img{ 0.0f, 0.0f, 375.0f, 166.0f };
	int MaxX = WINDOW_WIDTH - img.w, MaxY = WINDOW_HEIGHT - img.h;
	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, image[0]);
	bool loop = true;
	int imgCounter = 0;
	float32 speed = 0.5f;
	bool movement[2] = {true, true};
	while (loop) {
		SDL_Event ev; 
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym) {
				case SDLK_q:
				case SDLK_ESCAPE:
					loop = false;
					break;

				case SDLK_f:
				case SDLK_F11:
					if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
						SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
						SDL_SetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
						SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
						MaxX = WINDOW_WIDTH - img.w;
						MaxY = WINDOW_HEIGHT - img.h;
						img.x = 0, img.y = 0;
						speed = 0.5f;
					}
					else {
						SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
						SDL_SetWindowSize(window, dm.w, dm.h);
						MaxX = dm.w - img.w;
						MaxY = dm.h - img.h;
						img.x = 0, img.y = 0;
						speed = 1.0f;
					} break;
				}
			}
			else if (ev.type == SDL_QUIT) {
				loop = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		SDL_RenderCopyF(renderer, imageTexture, NULL, &img);
		SDL_RenderDrawRectF(renderer, &img);

		SDL_RenderPresent(renderer);

		
		SDL_UpdateWindowSurface(window);


		if (img.x < MaxX && movement[0])
			img.x += speed;
		else if (img.x > 0 && !movement[0])
			img.x -= speed;
		else if (img.x <= 0) {
			movement[0] = true;
			imgCounter = changeColor(imgCounter);
			imageTexture = SDL_CreateTextureFromSurface(renderer, image[imgCounter]);
		}
		else if (img.x >= MaxX) {
			movement[0] = false;
			imgCounter = changeColor(imgCounter);
			imageTexture = SDL_CreateTextureFromSurface(renderer, image[imgCounter]);
		}

		if (img.y < MaxY && movement[1])
			img.y += speed;
		else if (img.y > 0 && !movement[1])
			img.y -= speed;
		else if (img.y <= 0) {
			movement[1] = true;
			imgCounter = changeColor(imgCounter);
			imageTexture = SDL_CreateTextureFromSurface(renderer, image[imgCounter]);
		}
		else if (img.y >= MaxY) {
			movement[1] = false;
			imgCounter = changeColor(imgCounter);
			imageTexture = SDL_CreateTextureFromSurface(renderer, image[imgCounter]);
		}
	}


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	imageTexture = nullptr;
	SDL_Quit();

	return 0;
}
