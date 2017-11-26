#include <iostream>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	// the main window 
	SDL_Window* window = NULL;

	// SDL Surface 
	SDL_Surface* screenSurface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		// if something bad happens 
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	} else {
		window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "SDL Window couldn't be initialized! SDL_Error: " << SDL_GetError() << std::endl;
		} else {
			// get window surface 
			screenSurface = SDL_GetWindowSurface(window);

			// Fill the surface white 
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			// update the window surface 
			SDL_UpdateWindowSurface(window);

			// Wait two seconds 
			SDL_Delay(2000);			
		}
	}

	//Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
