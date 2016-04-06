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
	
NOTE:  I have INCLUDED an already-compiled 32-bit ELF file
	   in case you cannot compile it yourself.  It is named
	   simply as "game.elf".  You can type "./game.elf" to 
	   run it if you can not get the libraries working.
	
FIVE THINGS I UTILIZED FROM THIS CLASS IN THIS PROJECT:
	1.) Vectors. I use them extensively.  They actually are mainly vectors
			of structs, and the structs keep x/y coordinates.  You can see
			vectors being used in the Snake.cpp file
	2.) Friends.  I use one friend function in the Fruit.cpp file.
			It is a friend with the Snake class, because it needs to access
			the snake's x/y coordinates to know if it has been eaten.
	3.) Multiple file projects.  I did not actually know how to compile two
			files together before this class.  And I split this project up
			into many files, keeping them clean and simple.  I did end up making
			my Snake.cpp file pretty long, maybe I could refactor that into
			smaller parts with more classes.
	4.) Constructors.  I rarely use the default constructor for anything
			in this project.  In the Snake class, I mainly use the constructor
			to initialize constants, but usually the constructors
			are there to load the images for the Graphics class.
	5.) Composition.  My Game Class makes extensive use of composition.
			Following the "has-a" relationship, the Game has a snake, fruit,
			and a background.

KNOWN BUGS
	1.) Attempting to wrap around the edge with a tail will cause the tail to 
		go haywire, and possibly result in a segfault.
		
TODO:
	1.) Get a better Snake head picture
	2.) Add a start screen
	3.) Add a Game Over screen
	4.) Maybe add obstacles
