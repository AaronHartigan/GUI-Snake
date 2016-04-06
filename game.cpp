#include "game.h"
#include "graphics.h"
#include "input.h"
#include <iostream>
#include <SDL2/SDL.h>

// some "global" variables for this translation unit
namespace {
	const int FPS_CAP = 50;
	const int MIN_FRAME_MS = 1000/ FPS_CAP; //ms = miliseconds
}

Game::Game() {
	this->_gameOver = false;
	// initalize the timer used to control FPS
	SDL_Init(SDL_INIT_TIMER);
	// call the gameloop when this object is instantiated
	this->gameLoop();
}

Game::~Game() {

}

// The heart of the program!
void Game::gameLoop() {
	//instantiate our composition ojects
	Graphics graphics;
	Input input;
	SDL_Event event;
	this->_snake = Snake(graphics);
	this->_background = Background(graphics);
	this-> _fruit = Fruit(graphics);

	int frameCounter = 0;
	int renderingTime = 0;

	int TIME_BEFORE_LOGIC_MS = SDL_GetTicks();
	int ELAPSED_TIME_MS = 0;
	int ticksStartOfSecond = TIME_BEFORE_LOGIC_MS;
	int ticksEndOfSecond = TIME_BEFORE_LOGIC_MS;

	//main game loop
	while (!_gameOver) {
		//Grab the next event from the event queue.
		//Will loop through all events until the last one
		//pressed during the frame
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				input.keyDownEvent(event);
			}
			// else if the "close window" 'x' is clicked
			else if (event.type == SDL_QUIT) {
				this->_gameOver = true;
			}
			if (input.keyPressed(SDL_SCANCODE_ESCAPE)) {
				this->_gameOver = true;
			}
			else if (input.keyPressed(SDL_SCANCODE_LEFT) ||
					 input.keyPressed(SDL_SCANCODE_A)) {
				_snake.moveLeft();
			}
			else if (input.keyPressed(SDL_SCANCODE_RIGHT) ||
					 input.keyPressed(SDL_SCANCODE_D)) {
				_snake.moveRight();
			}
			else if (input.keyPressed(SDL_SCANCODE_UP) ||
					 input.keyPressed(SDL_SCANCODE_W)) {
				_snake.moveUp();
			}
			else if (input.keyPressed(SDL_SCANCODE_DOWN) ||
					 input.keyPressed(SDL_SCANCODE_S)) {
				_snake.moveDown();
			}
			input.clearKeyPresses();
		}
		// if the game logic is too fast, update using the minimum frame time instead
		this->update(std::max(ELAPSED_TIME_MS, MIN_FRAME_MS));
		this->draw(graphics);
		const int TIME_AFTER_LOGIC_MS = SDL_GetTicks();
		ELAPSED_TIME_MS = TIME_AFTER_LOGIC_MS - TIME_BEFORE_LOGIC_MS;

		if (ELAPSED_TIME_MS < MIN_FRAME_MS) {
			SDL_Delay(MIN_FRAME_MS - ELAPSED_TIME_MS);
		}

		TIME_BEFORE_LOGIC_MS = SDL_GetTicks();

		//framerate logic
		frameCounter++;
		renderingTime += ELAPSED_TIME_MS;
		if (frameCounter == FPS_CAP) {
			ticksEndOfSecond = TIME_BEFORE_LOGIC_MS;
			std::cout << "Framerate: " << (float) FPS_CAP * 1000 / (ticksEndOfSecond - ticksStartOfSecond) << std::endl;
			//std::cout << "Render Time: " << (float) renderingTime / 1000 << std::endl << std::endl;
			frameCounter = 0;
			renderingTime = 0;
			ticksStartOfSecond = ticksEndOfSecond;
		}
	}
	std::cout << "Final Score: " << _snake.getScore(_snake) << std::endl;
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	_background.draw(graphics);
	_fruit.draw(graphics);
	_snake.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	_snake.update(elapsedTime);
	_snake.updateMoveHistory();
	_snake.updateTailPosition(elapsedTime);
	if (_fruit.checkFruitCollision(_snake)) {
		do {
			_fruit.generateNewFruit();
		  // prevent fruit from spawning on snake
		} while (_fruit.checkFruitCollision(_snake));
		_snake.increaseScore();
		_snake.addTailNode();
	}
	if (_snake.checkTailCollision()) {
		this->_gameOver = true;
	}
}
