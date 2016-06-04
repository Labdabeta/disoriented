all:  
	g++ graphics.cpp sprites.cpp maze.cpp main.cpp -o astray_and_adrift.out `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_image -g
