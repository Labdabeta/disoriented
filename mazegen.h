#ifndef MAZEGEN_H
#define MAZEGEN_H

class wall{// these things are to mimic what already exists in python
    public:
        int x,y;
        string dir; 
        wall(int x2, int y2, string dir2){
            x=x2;
            y=y2;
            dir=dir2; 
        }
        bool operator==(const wall & other){
            return (this->x == other.x  && this->y==other.y &&this->dir == other.dir);
        }
};
std::vector<wall> getMaze(int width, int height, float density, int seed);

#endif /* MAZEGEN_H */
