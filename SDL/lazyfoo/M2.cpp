#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// Function prototypes 
bool init();
bool loadMedia();
void close();

// Some global stuff 
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init() {
	// init flag 
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO < 0)) {
		printf("SDL could not be initialized. SDL Error: %s\n", SDL_GetError());		
		success = false;		
	} else {
		gWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("SDL window could not be initialized. SDL Error: %s\n", SDL_GetError());		
			success = false;			
		} else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia() {
	bool success = true;

	// load splash image 
	gHelloWorld = SDL_LoadBMP("images/hello_world.bmp");
	if (gHelloWorld == NULL) {
		printf("Image couldn't be loaded. SDL Error: %s\n", SDL_GetError());		
		success = false;
	}
	return success;
}

void close() {
	// deallocate stuff 
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argc, char* args[]) {
	// main engine 
	if(!init()) {
		printf("Initialization failed!\n");
	} else {
		// load media 
		if (!loadMedia()) {
			printf("Failed to load media!\n");			
		} else {
			// Apply the image 
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

			// update the window 
			// the reason we do is because contents are rendered at the back buffer and 
			// what we see is the front buffer
			SDL_UpdateWindowSurface(gWindow);

			// delat 
			SDL_Delay(10000);
		}
	}

	// free the res
	close();
	return 0;
}
