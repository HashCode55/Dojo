#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// constants for key presses 
enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// Function prototypes 
bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

// Some global stuff 
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];

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

	// list of strings to iterate from 
	std::string files[] = {"press", "up", "down", "left", "right"};

	// load splash image 
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
		gKeyPressSurface[i] = loadSurface("images/" + files[i] + ".bmp");
		if (gKeyPressSurface[i] == NULL) {
			printf("Image couldn't be loaded. SDL Error: %s\n", SDL_GetError());		
			success = false;
		}
	}

	return success;
}

void close() {
	// deallocate stuff 
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
		SDL_FreeSurface(gKeyPressSurface[i]);
		gKeyPressSurface[i] = NULL;
	}

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if (surface == NULL) {
		printf("Image couldn't be loaded. SDL Error: %s\n", SDL_GetError());				
	}
	return surface;
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
			// quit flag 
			bool quit = false;			
			// SDL Event 
			SDL_Event e;

			gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
			// GAME LOOP
			while(!quit) {
				// EVENT LOOP
				// processes the event queue 
				while(SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					} else if (e.type == SDL_KEYDOWN) {
						// switch over the cases 
						switch (e.key.keysym.sym) {
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
							break;

							default:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}	
					}
				}
				// Apply the image 
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

				// update the window 
				// the reason we do is because contents are rendered at the back buffer and 
				// what we see is the front buffer
				SDL_UpdateWindowSurface(gWindow);	
			}						
		}
	}

	// free the res
	close();
	return 0;
}
