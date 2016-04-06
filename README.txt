README:

To compile this project, you need to two following libraries:

	SDL2
	SDL2-image
	
Use the following command-line to compile it:

	g++ *.cpp -lSDL2 -lSDL2_image
	
If you do not have the libraries, the code will not compile.
If you are on linux, you can use the following command-lines to get them:

	SDL2: 		 apt-get install libsdl2-dev
	SDL2-image:  apt-get install libsdl2-image-dev
	
KNOWN BUGS
	1.) Attempting to wrap around the edge with a tail will cause the tail to 
		go haywire, and possibly result in a segfault.
		
TODO:
	1.) Get a better Snake head picture
	2.) Add a start screen
	3.) Add a Game Over screen
	4.) Maybe add obstacles
