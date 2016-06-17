#include "input.h"


void Input::clearKeyPresses() {
	_pressedKeys.clear();
}

// Called when a key has been pressed
void Input::keyDownEvent(const SDL_Event& event) {
	this->_pressedKeys[event.key.keysym.scancode] = true;
}

//Checks to see if the key was pressed
bool Input::keyPressed(SDL_Scancode key) {
	return this->_pressedKeys[key];
}
