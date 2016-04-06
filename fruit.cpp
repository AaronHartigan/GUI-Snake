#include "fruit.h"
#include "snake.h"
#include "graphics.h"
#include "globals.h"
#include <stdlib.h>     /* abs */
#include <SDL2/SDL.h>

#include <iostream>

Fruit::Fruit() {}

Fruit::~Fruit() {}

Fruit::Fruit(Graphics &graphics) {
	srand( SDL_GetTicks() );
	this->_fruitTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
													   graphics.loadImage("fruit.png"));
	this->generateNewFruit();
}

// Checks collision by seeing if the bounding box of the fruit and snake overlap
bool Fruit::checkFruitCollision(Snake &snake) {
	int fruit_center_x = this->_x + FRUIT_RADIUS;
	int snake_center_x = snake._x + snake.SNAKE_WIDTH/2;

	int fruit_center_y = this->_y + FRUIT_RADIUS;
	int snake_center_y = snake._y + snake.SNAKE_HEIGHT/2;

	if ( abs(fruit_center_x - snake_center_x) < FRUIT_RADIUS + snake.SNAKE_WIDTH/2 &&
		 abs(fruit_center_y - snake_center_y) < FRUIT_RADIUS + snake.SNAKE_HEIGHT/2)
	{
		return true;
	}
	return false;
}

void Fruit::generateNewFruit() {
	// the "- RADIUS * 2" prevents the fruit from spawning out of bounds
	this->_x = rand() % (globals::SCREEN_WIDTH - FRUIT_RADIUS * 2);
	this->_y = rand() % (globals::SCREEN_HEIGHT - FRUIT_RADIUS * 2);
}

void Fruit::draw(Graphics &graphics) {
	int size = this->FRUIT_RADIUS*2;
	SDL_Rect srcRect = { 0, 0, size, size };
	SDL_Rect dstRect = { this->_x, this->_y, size, size };

	graphics.blitSurface(this->_fruitTexture, &srcRect, &dstRect);
}
