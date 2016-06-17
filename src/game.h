#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "background.h"
#include "fruit.h"

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);
	bool _gameOver;

	Snake _snake;
	Background _background;
	Fruit _fruit;
};

#endif
