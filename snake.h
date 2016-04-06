#ifndef SNAKE_H
#define SNAKE_H

#include "fruit.h"
#include <vector>
#include <string>

class Graphics;
struct SDL_Texture;

class Snake {

public:
	Snake();
	Snake(Graphics &graphics);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();

	bool checkTailCollision();
	void addTailNode();
	void updateMoveHistory();
	void updateTailPosition(float elapsedTime);

	void increaseScore();
	int getScore(Snake &snake);

private:
	enum
	{
		SNAKE_WIDTH = 20,
		SNAKE_HEIGHT = 20,
		SNAKE_RADIUS = 10,
		TAIL_WIDTH = 10,
		TAIL_HEIGHT = 10,
		TAIL_RADIUS = 5
	};
	float _dx, _dy; //change in coordinates during frame
	float _x, _y;
	unsigned
	int _score;
	SDL_Texture* _snakeTextureRight;
	SDL_Texture* _snakeTextureDown;
	SDL_Texture* _snakeTextureLeft;
	SDL_Texture* _snakeTextureUp;
	SDL_Texture* _tailTexture;
	std::string _direction;

	// A friend function
	friend bool Fruit::checkFruitCollision(Snake &snake);

	struct tailCoords {
		float x;
		float y;
		float distanceFromHead;
	};
	std::vector<tailCoords> tail;

	//  A three-tuple of information of where the snake has turned.
	//  Needed for having the tail follow the snake.
	//  The direction stored is the direction that the path was.
	//
	//			<------
	//			|
	//			|
	//		<---V
	//
	//  Like so. The arrows represent the direction.
	//  The beginning Corner node will ALWAYS be the current location
	//  of the snake's head.
	struct Corners {
		float x;
		float y;
		std::string direction;
	};
	std::vector<Corners> history;
	int _historyLength;
	int _distanceBetweenTailNodes;
};

#endif
