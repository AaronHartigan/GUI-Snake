#include "background.h"
#include "graphics.h"
#include <SDL2/SDL.h>

Background::Background() {}

Background::~Background() {}

// This constructor will load the background image
Background::Background(Graphics &graphics) {
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
															graphics.loadImage("../resources/background.png"));

}

void Background::draw(Graphics &graphics) {
	graphics.blitSurface(this->_backgroundTexture);
}
