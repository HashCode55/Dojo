#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// func prototypes 
bool init();
void close();

// globals 
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init() {
	// init flag 
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO < 0)) {
		printf("SDL could not be initialized. SDL Error: %s\n", SDL_GetError());		
		success = false;		
	} else {
		// create the window 
		gWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("SDL window could not be initialized. SDL Error: %s\n", SDL_GetError());		
			success = false;			
		} else {
			// initialize the rendered			
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not initialize! SDL Error: %s\n", SDL_GetError());	
				success = false;
			} else {
				// renderer color 
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);	

				// Initialize PNG Loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;				
				} 
			}			
		}
	}

	return success;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main() {
	if (!init()) {
		printf("Initialization failed!\n");
	} else {
		bool quit = false;
		SDL_Event e;

		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);	
			SDL_RenderClear(gRenderer);
			// render a red filled quad 
			SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, &fillRect);

			SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawRect(gRenderer, &outlineRect);

			// Draw blue horizontal line in middle 
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

			// Draw vertical yello dots 
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
			for (int i = 0; i < SCREEN_WIDTH; i += 4) {
				SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
			}

			SDL_RenderPresent(gRenderer);
		}
		
	}
	close();
	return 0;
}