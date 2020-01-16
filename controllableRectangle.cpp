// include declarations
#include <SDL.h>
#include <iostream>
#include <string>

// screen constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

// rectangle size
int rectangleWidth = 50;
int rectangleHeight = 50;

// rectangle position
int rectangleX = SCREEN_WIDTH/2 - rectangleWidth;
int rectangleY = SCREEN_HEIGHT/2 - rectangleHeight;

// speed
int speed = 10;

// the window
SDL_Window* gWindow;

// the renderer
SDL_Renderer* gRenderer;

// the init function
void init() {
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("Controllable Rectangle - 1/16/2020", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

// the loadMedia function
void loadMedia() {
	// nothing to load
}

// the cleanup function
void cleanUp() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

// the draw rectangle function
void drawRectangle(int x, int y, int width, int height) {
	SDL_Rect drawRect = {x, y, width, height};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &drawRect);
}

// the check keystates function
void checkKeyStates() {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	// if up and left
	if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (rectangleY > speed && rectangleX > speed) {
			rectangleY = rectangleY - speed;
			rectangleX = rectangleX - speed;
		}
		else if (rectangleY > speed) {
			rectangleY = rectangleY - speed;
		}
		else if (rectangleX > speed) {
			rectangleX = rectangleX - speed;
		}
	}
	// if up and right
	else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (rectangleY > speed && rectangleX < SCREEN_WIDTH - speed - rectangleWidth) {
			rectangleY = rectangleY - speed;
			rectangleX = rectangleX + speed;
		}
		else if (rectangleY > speed) {
			rectangleY = rectangleY - speed;
		}
		else if (rectangleX < SCREEN_WIDTH - speed - rectangleWidth) {
			rectangleX = rectangleX + speed;
		}
	}
	// if down and left
	else if ((currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT])) {
		if (rectangleY < SCREEN_HEIGHT - speed - rectangleHeight && rectangleX > speed) {
			rectangleY = rectangleY + speed;
			rectangleX = rectangleX - speed;
		}
		else if (rectangleY < SCREEN_HEIGHT - speed - rectangleHeight) {
			rectangleY = rectangleY + speed;
		}
		else if (rectangleX > speed) {
			rectangleX = rectangleX - speed;
		}
	}
	// if down and right
	else if ((currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT])) {
		if (rectangleY < SCREEN_HEIGHT - speed - rectangleHeight && rectangleX < SCREEN_WIDTH - speed - rectangleWidth) {
			rectangleY = rectangleY + speed;
			rectangleX = rectangleX + speed;
		}
		else if (rectangleY < SCREEN_HEIGHT - speed - rectangleHeight) {
			rectangleY = rectangleY + speed;
		}
		else if (rectangleX < SCREEN_WIDTH - speed - rectangleWidth) {
			rectangleX = rectangleX + speed;
		}
		
	}
	// if only up
	else if (currentKeyStates[SDL_SCANCODE_UP]) {
		if (rectangleY > speed) {
			rectangleY = rectangleY - speed;
		}
	}
	// if only down
	else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		if (rectangleY < SCREEN_HEIGHT - speed - rectangleHeight) {
			rectangleY = rectangleY + speed;
		}
	}
	// if only left
	else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (rectangleX > speed) {
			rectangleX = rectangleX - speed;
		}
	}
	// if only right
	else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (rectangleX < SCREEN_WIDTH - speed - rectangleWidth) {
			rectangleX = rectangleX + speed;
		}
	}
	else {
		
	}
}
// the main function
int main(int argc, char* args[]) {
	init();
	loadMedia();
	SDL_Event e;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		drawRectangle(rectangleX, rectangleY, rectangleWidth, rectangleHeight);
		checkKeyStates();
		SDL_RenderPresent(gRenderer);
	}
	cleanUp();
}