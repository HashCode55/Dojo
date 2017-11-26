#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

// Some global stuff 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


// Wrapper class for texture 
class LTexture {
public:
	// constructor
	LTexture();
	// destructor 
	~LTexture();	
	// housekeeping functions 
	bool loadFromFile(std::string path);
	int getHeight();
	int getWidth();	
	void render(int x, int y, SDL_Rect* clip);
	void free();

private:	
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

// constructor 
LTexture::LTexture () {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

// destructor 
LTexture::~LTexture() {
	free();
}

bool LTexture::loadFromFile (std::string path) {
	// remove any reloaded texture 
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		printf("SDL_Image couldn't load image. SDL_Image Error: %s\n", IMG_GetError());
	} else {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
		if (newTexture == NULL) {
			printf("SDL couldn't convert surface to texture. SDL Error: %s\n", SDL_GetError());			
		} else {
			mWidth = surface->w;
			mHeight = surface->h;			
		}
		SDL_FreeSurface(surface);
	}
	mTexture = newTexture;
	return mTexture != NULL;	
}

int LTexture::getHeight () {
	return mHeight;	
}

int LTexture::getWidth () {
	return mWidth;
}

void LTexture::render (int x, int y, SDL_Rect* clip) {
	// make a rect if you want to render somewwhere else 	
	SDL_Rect rect = {x, y, mWidth, mHeight};
	if (clip != NULL) {
		rect.w = clip->w;
		rect.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &rect);
}

void LTexture::free () {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture gSpriteSheet;

// function declarations 
bool init();
bool loadMedia();
void close();

bool init () {	
	// set up SDL 
	// configuration 
	// Set up SLD Image to load png images 
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO < 0)) {
		printf("SDL couldn't be initialized. SDL Error: %s\n", SDL_GetError());
		success = false;		
	} else {
		// create main window 
		gWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("SDL Window couldn't be initialized. SDL Error: %s\n", SDL_GetError());
			success = false;			
		} else {
			// initialize the renderer
			// sync the render call with the vertical refresh rate of the machine 
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				printf("SDL Renderer couldn't be initialized. SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {				
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// initialze SDL Image 
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL Image couldn't be initialized. SDL Error: %s\n", IMG_GetError());
					success = false;
				}				
			}
		}
	}
	return success;
}	

bool loadMedia () {
	bool success = true;
	if (!gSpriteSheet.loadFromFile("images/foo.png")) {
		printf("File couldn't be loaded\n");
		success = false;		
	} else {
		// break it into rectangles 
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 64;
		gSpriteClips[0].h = 205;

		gSpriteClips[1].x = 64;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 64;
		gSpriteClips[1].h = 205;

		gSpriteClips[2].x = 128;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 64;
		gSpriteClips[2].h = 205;

		gSpriteClips[3].x = 196;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 64;
		gSpriteClips[3].h = 205;
	}
	return success;
}

void close () {
	gSpriteSheet.free();

	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}


int main () {
	if (!init()) {
		printf("Couldn't start SDL.\n");		
	} else {
		if (!loadMedia()) {
			printf("Couldn't load media.\n");		
		} else {
			bool quit = false;
			SDL_Event e;
			int frame = 0;
			// game loop
			while (!quit) {
				// event loop
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear(gRenderer);

				SDL_Rect* current = &gSpriteClips[frame / 4];
				gSpriteSheet.render((SCREEN_WIDTH - current->w) / 2, (SCREEN_HEIGHT - current->h) / 2, current);
				SDL_RenderPresent(gRenderer);

				++frame;

				if (frame / 4 >= WALKING_ANIMATION_FRAMES) {
					frame = 0;
				}
			}
		}
	}
}
