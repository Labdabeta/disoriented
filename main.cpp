#include <SDL2/SDL.h>

#include "graphics.h"
#include "maze.h"

class AstrayAndAdrift : public Graphics
{// private:
    Maze maze;
    public:
        AstrayAndAdrift() {
        
        }
        bool onStep() { maze.onStep(); return false; }
        void onDraw() { maze.onDraw(*this); }
        void onA() {}
        void onB() {}
        void onC() {}
        void onD() {}
        void onE() {}
        void onF() {}
        void onUp() { maze.onUp(); }
        void onDown() { maze.onDown(); }
        void onRight() { maze.onRight(); }
        void onLeft() { maze.onLeft(); }
};

int main(int argc, char *argv[])
{
    AstrayAndAdrift g;

    g.run();

    return 0;
}
