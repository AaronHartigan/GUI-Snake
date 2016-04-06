#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>

class Graphics;
struct SDL_Texture;

class Background {
public:
	Background();
	Background(Graphics &graphics);
	~Background();
	void draw(Graphics &graphics);

private:
	SDL_Texture* _backgroundTexture;
};

#endif
