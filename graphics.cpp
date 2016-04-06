#include "graphics.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH,
								globals::SCREEN_HEIGHT,
								0,
								&this->_window,
								&this->_renderer);
	SDL_SetWindowTitle(this->_window, "Aaron's C++ Final Project");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
	//if an image is not loaded, load it
	if (this->_imageGallery.count(filePath) == 0) {
		this->_imageGallery[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_imageGallery[filePath];
}

// The source and destination rectangles are default-valued to NULL.
// This causes whatever image is loaded to automatically scale to the
// size of the window.  This is useful for the background image.
void Graphics::blitSurface(SDL_Texture* texture,
						   SDL_Rect* srcRect,
						   SDL_Rect* dstRect) {
	SDL_RenderCopy(this->_renderer, texture, srcRect, dstRect);
}

void Graphics::flip() {
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->_renderer;
}
