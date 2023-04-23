This was my submission for COMP2004 (v.1) Computer Graphics At Curtin. The assignment task was to make a scene with at least 8 different textures and 2 unique animations. Unfortunately this unit isn't run by Curtin any more :(

OpenGL Minecraft Scene

Author: Austin Bevacqua

Prerequisites
    The program requires a instaliation of 
	- The GCC/G++ C compiler.
	- OpenGL
	- GLSL
	- GLM
	- CMake

Overall design and functionality
	The scene created is a 3D Minecraft-inspired scene.
	Commands:
		- P to switch between perspective and orthographic projection
		- O to switch between "light" and "darkish" scenery
		- K to make the scene brighter
		- L to make the scene darker
		- R to open the chest and start an animation
		- F to keep the light source in place
		- SHIFT to double camera speed
		- WASD to move around
 	For a more detailed description about the scene, please read the included report.

Compiling/Running the program (On Linux)
    -Simply run the .sh script "create.sh" to automatically build and run the program.
	./create.sh
    -If this does not work for whatever reason, navigate into the build directory (20162896 CG Assignment/build) and run these commands
	cmake ../
	make
	cd bin/assignment/
	./assignment__opengl

Special Thanks:
- Joey De Vriez for his excellent "LearnOpenGL" tutorials. This program is enormously inspired by the code and ideas from his website.


    
