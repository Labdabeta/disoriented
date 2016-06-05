all:  
	g++ sounds.cpp mrhuggz.cpp genitem.cpp mazegen.cpp graphics.cpp sprites.cpp maze.cpp main.cpp -o astray_and_adrift.out `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -g

windows:
	/opt/mingw32/bin/i686-w64-mingw32-g++ sounds.cpp mrhuggz.cpp genitem.cpp mazegen.cpp graphics.cpp sprites.cpp maze.cpp main.cpp -o astray_and_adrift.exe -I/home/louis/winSDL/SDL2-2.0.4/i686-w64-mingw32/include -D_REENTRANT -L/home/louis/winSDL/SDL2-2.0.4/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -m32 -std=c++11
	
