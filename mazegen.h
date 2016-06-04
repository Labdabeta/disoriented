#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <vector>
#include <string>

class wall{// these things are to mimic what already exists in python
    public:
        int x,y;
        std::string dir; 
        wall(int x2, int y2, std::string dir2){
            x=x2;
            y=y2;
            dir=dir2; 
        }
        bool operator==(const wall & other){
            return (this->x == other.x  && this->y==other.y &&this->dir == other.dir);
        }
};
std::vector<wall> genMaze(int width, int height, float density);

#endif /* MAZEGEN_H */
