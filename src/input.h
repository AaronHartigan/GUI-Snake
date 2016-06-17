#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>


//try to comment these out
struct SDL_Window;
struct SDL_Renderer;

class Input {
public:
	void clearKeyPresses();
	void keyDownEvent(const SDL_Event& event);
	bool keyPressed(SDL_Scancode key);

private:
	std::map<SDL_Scancode, bool> _pressedKeys;
};

#endif
