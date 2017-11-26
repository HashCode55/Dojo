// VIEWPORTS 
// Sometimes we wan to render only a part of screen 
// and this is what viewport does!
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

class LTexture {
	// A wrapper for SDL_Texture 
public:
	LTexture();
	// deallocates memory 
	~LTexture();
	// load from file 
	bool loadFromFile(std::string path);
	// for freeing the texture 
	void free();
	// to render texture at a given point 
	void render(int x, int y, SDL_Rect* rect);
	// get image dimentions 
	int getWidth();
	int getHeight();
private:
	// texture 
	SDL_Texture* mTexture;
	// dimentions 
	int mWidth;
	int mHeight;	
};

LTexture::LTexture () {
	//initialize 
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture () {
	free();
}

// Some global stuff 
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect gSpriteClips[4];
LTexture gSpriteSheetTexture;

bool LTexture::loadFromFile(std::string path) {
	// get rid of persisting texture
	free();
	SDL_Texture* newTexture = NULL;
	// convert "surface" to texture 
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		printf("Couldn't load image. SDL_Image error: %s\n", IMG_GetError());
	} else {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
		// create the texture from the surface object 
		newTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
		if (newTexture == NULL) {
			printf("Couldn't covert surface to texture. SDL error: %s\n", SDL_GetError());			
		} else {
			mWidth = surface->w;
			mHeight = surface->h;			
		}
		SDL_FreeSurface(surface);		
	}
	mTexture = newTexture;
	return mTexture != NULL;	
}


void LTexture::free() {
	// free the texture if not null 
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;		
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
	// reserves the place of the texture in the window 
	SDL_Rect rect = {x, y, mWidth, mHeight};
	// the part of texture we want to clip 
	if (clip != NULL) {
		rect.w = clip->w;
		rect.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &rect);
}

int LTexture::getHeight() {
	return mHeight;	
}

int LTexture::getWidth() {
	return mWidth;	
}

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

bool loadMedia() {
	bool success = true;

	if (!gSpriteSheetTexture.loadFromFile("images/dots.png")) {
		printf("Failed to load the image.\n");
		success = false;
	} else {
		// populate the array of clips 
		// x and y are the location on sprite sheet
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
	}
	return success;
}

void close() {
	gSpriteSheetTexture.free();		

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
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear(gRenderer);

				gSpriteSheetTexture.render(0, 0, &gSpriteClips[0]);
				gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);
				gSpriteSheetTexture.render(0, SCREEN_HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);
				gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[3].w, SCREEN_HEIGHT - gSpriteClips[3].h, &gSpriteClips[3]);
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
