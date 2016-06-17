# Snake
The classic game of Snake in C++ using SDL2.0 for window creation and graphics.

### Screenshots



### Dependencies

For linux:
`SDL2: 		  apt-get install libsdl2-dev`

`SDL2-image:  apt-get install libsdl2-image-dev`
	
For Windows:

[SDL2](https://www.libsdl.org/download-2.0.php)

[SDL2-image](https://www.libsdl.org/projects/SDL_image/)

To compile this in Linux:

`g++ *.cpp -lSDL2 -lSDL2_image`

	
### Known Bugs
* Attempting to wrap around the edge with a tail will cause the tail to go haywire, and possibly result in a segfault.
		
### TODO:
* Get a better Snake head picture
* Add a start and game over screen
* Show Score
* Difficulty adjustor
