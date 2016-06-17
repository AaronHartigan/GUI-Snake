#ifndef FRUIT_H
#define FRUIT_H

class Graphics;
class Snake;
struct SDL_Texture;

class Fruit {
public:
	Fruit();
	Fruit(Graphics &graphics);
	~Fruit();
	void draw(Graphics &graphics);
	bool checkFruitCollision(Snake &snake);
	void generateNewFruit();
private:
	enum {
		FRUIT_RADIUS = 10
	};
	int _x, _y;
	SDL_Texture* _fruitTexture;
};

#endif
