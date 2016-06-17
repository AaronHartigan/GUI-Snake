#include "snake.h"
#include "graphics.h"
#include "globals.h"
#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

namespace snake_constants {
	const float SLITHER_SPEED = 0.2f;
}

Snake::Snake() {}

Snake::Snake(Graphics &graphics) {
	// Load snake image
	this->_snakeTextureRight = SDL_CreateTextureFromSurface(graphics.getRenderer(),
													   graphics.loadImage("../resources/snakeright.png"));
	this->_snakeTextureDown = SDL_CreateTextureFromSurface(graphics.getRenderer(),
													   graphics.loadImage("../resources/snakedown.png"));
	this->_snakeTextureLeft = SDL_CreateTextureFromSurface(graphics.getRenderer(),
													   graphics.loadImage("../resources/snakeleft.png"));
	this->_snakeTextureUp = SDL_CreateTextureFromSurface(graphics.getRenderer(),
													   graphics.loadImage("../resources/snakeup.png"));
	this->_tailTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
													   graphics.loadImage("../resources/tail.png"));
	this->_direction = "right";				 // starting direction
	this->_x = globals::SCREEN_WIDTH / 10;   // x-starting position
	this->_y = globals::SCREEN_HEIGHT / 10;  // y-starting position

	this->_dx = snake_constants::SLITHER_SPEED;  // Start by moving to the right
	this->_dy = 0;								 // Start without moving up or down
	this->_score = 0;
	Corners node1 = { this->_x, this->_y, "right" };
	history.insert(history.begin(), node1);
	Corners node2 = { 0, this->_y, "right" };
	history.insert(history.begin(), node2);
	Corners node3 = { 0, 0, "down" };
	history.insert(history.begin(), node3);
	this->_historyLength = this->_x + this->_y;
	_distanceBetweenTailNodes = (TAIL_RADIUS * 2) * 1.6;
}

void Snake::moveLeft() {
	if (this->_direction != "right") {
		this->_dx = -snake_constants::SLITHER_SPEED;
		this->_dy = 0;
		this->_direction = "left";
	}
}
void Snake::moveRight() {
	if (this->_direction != "left") {
		this->_dx = snake_constants::SLITHER_SPEED;
		this->_dy = 0;
		this->_direction = "right";
	}

}void Snake::moveUp() {
	if (this->_direction != "down") {
		this->_dy = -snake_constants::SLITHER_SPEED;
		this->_dx = 0;
		this->_direction = "up";
	}
}

void Snake::moveDown() {
	if (this->_direction != "up") {
		this->_dy = snake_constants::SLITHER_SPEED;
		this->_dx = 0;
		this->_direction = "down";
	}
}

void Snake::increaseScore() {
	this->_score++;
	std::cout << "Score: " << _score << std::endl;
}

// unused
int Snake::getScore(Snake &snake) {
	return this->_score;
}

void Snake::update(float elapsedTime) {
	//Move snake by _dx.  Then check if snake should "loop around"
	this->_x += _dx * elapsedTime;
	if (this->_x >= globals::SCREEN_WIDTH) {	// if off the right of screen
		this->_x -= globals::SCREEN_WIDTH;		// move to the left
	}
	else if (this->_x < 0) {					// if off the left of screen
		this->_x += globals::SCREEN_WIDTH;		// move to the right
	}

	//Move snake by _yx.  Then check if snake should "loop around"
	this->_y += _dy * elapsedTime;
	if (this->_y >= globals::SCREEN_HEIGHT) {  // if below the bottom of screen
		this->_y -= globals::SCREEN_HEIGHT;	   // move back to the top
	}
	else if (this->_y < 0) {				   // if off the top screen
		this->_y += globals::SCREEN_HEIGHT;	   // move back to the bottom
	}
}

// Checks tail collision by seeing if the bounding box of the snake head
// and each of the tail nodes overlap
bool Snake::checkTailCollision() {
	int snake_center_x = this->_x + SNAKE_WIDTH/2;
	int snake_center_y = this->_y + SNAKE_HEIGHT/2;

	for (std::vector<tailCoords>::iterator it = tail.begin(); it != tail.end(); it++) {
		int tail_center_x = it->x + TAIL_RADIUS;
		int tail_center_y = it->y + TAIL_RADIUS;

		if ( abs(tail_center_x - snake_center_x) < TAIL_RADIUS + SNAKE_RADIUS &&
			 abs(tail_center_y - snake_center_y) < TAIL_RADIUS + SNAKE_RADIUS)
		{
			return true;
		}
	}
	return false;
}

// adds a new snake tail node to the back of the snake's tail vector.
void Snake::addTailNode() {


	//** Calculate where the new tail node should be **//
	//The +1 causes the first tail section to be farther back than the others;
	//if it is too close, it will automatically collide with the snake.
	float tailDistanceFromHead = (this->_score + 1) * _distanceBetweenTailNodes;
	float distanceLeftToMove = tailDistanceFromHead;

	std::string tail_direction;

	// the two coordinates for the new tail node.
	// these coordinates start at the snake's head and
	// will be "pushed down" through the tail,
	// following the history vector.
	float tail_x = history.begin()[0].x;
	float tail_y = history.begin()[0].y;
	float distanceToCorner;
	std::vector<Corners>::iterator hit = history.begin();
	while ( distanceLeftToMove > 0.0f && (hit+1) != history.end() ) {

		tail_direction = hit->direction;

		// DistanceToCorner is the distance between the current
		// tail node point and the next Corner history node
		if (tail_direction == "right" || tail_direction == "left") {
			distanceToCorner = abs(tail_x - (hit+1)->x);  // note: X
		}
		else {
			distanceToCorner = abs(tail_y - (hit+1)->y);  // note: Y
		}

		if ( distanceLeftToMove < distanceToCorner ) {
			if (tail_direction == "right")
				tail_x -= distanceLeftToMove;
			else if (tail_direction == "left")
				tail_x += distanceLeftToMove;
			else if (tail_direction == "down")
				tail_y -= distanceLeftToMove;
			else if (tail_direction == "up")
				tail_y += distanceLeftToMove;
			distanceLeftToMove = 0;
		}
		else {
			if (tail_direction == "right")
				tail_x -= distanceToCorner;
			else if (tail_direction == "left")
				tail_x += distanceToCorner;
			else if (tail_direction == "down")
				tail_y -= distanceToCorner;
			else if (tail_direction == "up")
				tail_y += distanceToCorner;
			distanceLeftToMove -= distanceToCorner;
		}
		hit++;
	}
	//** END: Calculate where the new tail node should be **//

	//create new tail node with cacluated information
	tailCoords tailSection = { tail_x, tail_y, tailDistanceFromHead };
	//add node to tail vector
	tail.push_back(tailSection);
}

void Snake::updateTailPosition(float elapsedTime) {
	float historyDistance = 0.0f;  //used to keep track of how far back in the tail we have travelled
	std::vector<Corners>::iterator hit;
	std::vector<tailCoords>::iterator it;
	for (it = tail.begin(); it != tail.end(); it++) {
		float distanceToMove = snake_constants::SLITHER_SPEED * elapsedTime;
		float distanceFromHead = it->distanceFromHead;
		historyDistance = 0.0f;
		hit = history.begin();
		// Find the appriopriate corner to start from.
		// Add up the distance from all the previous corners until the distance
		// is large enough.
		while ( (hit+1) != history.end() ) {
			// add the length of the segment between the corners
			if (hit->direction == "right" || hit->direction == "left")
				historyDistance += abs(hit->x - (hit+1)->x);
			else
				historyDistance += abs(hit->y - (hit+1)->y);

			if (historyDistance > distanceFromHead)
				break;
			hit++;
		}

		while (distanceToMove > 0.0f) {
			// distance between tail node's current coordinates and the next Corner history node
			float distanceNodeAndCorner;
			std::string tailDirection = hit->direction;
			if (tailDirection == "right" || tailDirection == "left") {
				distanceNodeAndCorner = abs(it->x - hit->x);
			}
			else if (tailDirection == "up" || tailDirection == "down") {
				distanceNodeAndCorner = abs(it->y - hit->y);
			}
			if ( distanceNodeAndCorner >= distanceToMove ) {
				if (tailDirection == "right")
					it->x += distanceToMove;
				else if (tailDirection == "left")
					it->x -= distanceToMove;
				else if (tailDirection == "down")
					it->y += distanceToMove;
				else if (tailDirection == "up")
					it->y -= distanceToMove;
				distanceToMove = 0.0f;
			}
			else {
				if (tailDirection == "right")
					it->x += distanceNodeAndCorner;
				else if (tailDirection == "left")
					it->x -= distanceNodeAndCorner;
				else if (tailDirection == "down")
					it->y += distanceNodeAndCorner;
				else if (tailDirection == "up")
					it->y -= distanceNodeAndCorner;
				distanceToMove -= distanceNodeAndCorner;
				hit--;
			}
		}
	}
}

void Snake::updateMoveHistory() {
	float old_x = history.begin()->x;
	float old_y = history.begin()->y;
	// These next two lines are kind of a hack to make the tail follow
	// from the center of the snake, rather than the upper-left corner,
	// which is the relative (0,0) of the snake.
	float new_x = this->_x + SNAKE_RADIUS - TAIL_RADIUS;
	float new_y = this->_y + SNAKE_RADIUS - TAIL_RADIUS;
	this->_historyLength += abs(old_x - new_x) + abs(old_y - new_y);

	// if snake is travelling same direction, update first history node
	if (history.begin()->direction == this->_direction ) {
		history.begin()->x = new_x;
		history.begin()->y = new_y;
	}
	// if change directions, add new Corner node to history
	else {
		Corners node = { new_x, new_y, this->_direction };
		history.insert(history.begin(), node);
		//std::cout << "Vector size: " << history.size() << std::endl;
	}

	//the distance between the last two nodes in history
	float lastLength = abs(history.end()[-2].x - history.end()[-1].x) +
					   abs(history.end()[-2].y - history.end()[-1].y);

	// If our history vector is holing more information than it needs,
	// delete the last element to save some space.
	//TODO: fix magic numbers
	float tailMemory = (this->_score + 3) * _distanceBetweenTailNodes * 2;
	if ( (this->_historyLength - lastLength) > tailMemory && history.size() > 3) {
		history.pop_back();
		_historyLength -= lastLength;
	}
}

void Snake::draw(Graphics &graphics) {
	//draw all tail nodes
	//iterate through tail vector
	for (std::vector<tailCoords>::iterator it = tail.begin(); it != tail.end(); it++) {
		SDL_Rect srcRect = { 0, 0, this->TAIL_WIDTH, this->TAIL_HEIGHT };
		SDL_Rect dstRect = { (int) it->x, (int) it->y, this->TAIL_WIDTH, this->TAIL_HEIGHT };
		graphics.blitSurface(this->_tailTexture, &srcRect, &dstRect);
	}

	// draw snake head
	SDL_Rect srcRect = { 0, 0, this->SNAKE_WIDTH, this->SNAKE_HEIGHT };
	SDL_Rect dstRect = { (int) this->_x, (int) this->_y, this->SNAKE_WIDTH, this->SNAKE_HEIGHT };
	if (this->_direction == "right")
		graphics.blitSurface(this->_snakeTextureRight, &srcRect, &dstRect);
	else if (this->_direction == "down")
		graphics.blitSurface(this->_snakeTextureDown, &srcRect, &dstRect);
	else if (this->_direction == "left")
		graphics.blitSurface(this->_snakeTextureLeft, &srcRect, &dstRect);
	else if (this->_direction == "up")
		graphics.blitSurface(this->_snakeTextureUp, &srcRect, &dstRect);
}
