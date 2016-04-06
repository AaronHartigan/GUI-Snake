#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>
#include <SDL2/SDL_image.h>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	SDL_Surface* loadImage(const std::string &filePath);
	void blitSurface(SDL_Texture* source,
					 SDL_Rect* srcRect = NULL,
					 SDL_Rect* dstRect = NULL);

	//"reveals" the rendered material to the screen
	void flip();

	//clears the screen
	void clear();

	//returns the renderer
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _imageGallery;
};

#endif
