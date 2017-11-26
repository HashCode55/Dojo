#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// Function prototypes 
bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);

// Some global stuff 
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

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

SDL_Texture* loadTexture(std::string path) {
	SDL_Texture* texture = NULL;

	// load image from specifie dpath 
	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == NULL) {
		// error 
		printf("Couldn't load the image. SDL_Image error: %s\n", IMG_GetError());		
	} else {
		// create texture from pixels 
		texture = SDL_CreateTextureFromSurface(gRenderer, surface);
		if (texture == NULL) {
			printf("Couldn't create the texture. SDL error: %s\n", SDL_GetError());		
		}
		// get rid of the surface 
		SDL_FreeSurface(surface);
	}
	return texture;
}

bool loadMedia() {
	bool success = true;

	gTexture = loadTexture("images/texture.png");
	if (gTexture == NULL) {
		printf("Failed to load texture.\n");
		success = false;
	} 
	return success;
}

void close() {
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;	
	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
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
			// quit flag 
			bool quit = false;			
			// SDL Event 
			SDL_Event e;
			
			// GAME LOOP
			while(!quit) {
				// EVENT LOOP
				// processes the event queue 
				while(SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					} 
				}

				// clear screen 
				// image this like throwing a bucket of paint to clear 
				SDL_RenderClear(gRenderer);

				// Render texture to screen 
				// The renderer starts its work 
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// update 
				// from back buffer to front buffer
				SDL_RenderPresent(gRenderer);
			}						
		}
	}

	// free the res
	close();
	return 0;
}
