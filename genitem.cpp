#include "genitem.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>

using namespace std;

int randint(int low, int high){
    return (rand() % (high-low+1))+low;
}

int sqrDist(int x, int y){
    int c= x*x+y*y;
    return c;
}

int distance(int sourcex, int sourcey, int destx, int desty) {
    int deltX = sourcex-destx;
    int deltY = sourcey-desty;
    return sqrt((deltX*deltX)+(deltY*deltY));
}

vector<int> generateThing(int playerX, int playerY, int xDim, int yDim, int minDist){
    bool done = false;

    vector<int> ret;

    while (!done) {
        ret.clear();
        ret.push_back(rand() % xDim);
        ret.push_back(rand() % yDim);
        if (distance(ret[0],ret[1],playerX,playerY) < minDist) {
            done = false;
        }
        else {
            done = true;
        }
    }

    return ret;
    
    /*
    cout<<"generateThing("<<playerX<<","<<playerY<<","<<xDim<<","<<yDim<<","<<minDist<<")"<<endl;
    int sqrDist2 = minDist*minDist;
    //choose the corner farthest from the player
    int tl=sqrDist(0-playerX,0-playerY);
    int tr=sqrDist(xDim-1-playerX,0-playerY);
    int bl=sqrDist(0-playerX,yDim-1-playerY);
    int br=sqrDist(xDim-1-playerX,yDim-1-playerY);
    //get the max of them:
    vector<int> ways = {tl, tr, bl, br};
    for (int i=0;i<4;i++){
        if(ways[i]<sqrDist2){
            ways[i] = -1;
        }
    }
    if (ways[0] == -1 && ways[1] == -1 && ways[2] == -1 && ways[3] == -1) {
        vector<int> ret = {0,0};
        cout<<"Too big on generateThing("<<playerX<<","<<playerY<<","<<xDim<<","<<yDim<<","<<minDist<<")"<<endl;
        return ret;
    }
        
    int thisMax = -1;
    while(thisMax == -1 || ways[thisMax] == -1){
        thisMax = randint(0,3);
    }
    int up;
    int left;
    switch(thisMax){
        case 0:{
        up=1;
        left=1;
        break;
    }
        case 1:{
        up=1;
        left=-1;
        break;
    }
        case 2:{
        up=-1;
        left=1;
        break;
    }
        case 3:{
        up=-1;
        left=-1;
        break;
    }
    }
    int randX = randint(0,xDim-1);
    int randY = randint(0,yDim-1);
    randX = playerX;
    randY = playerY;
    while((randX-playerX)*(randX-playerX)+(randY-playerY)*(randY-playerY) < sqrDist2){
        //jump towards the corner we're going for
        if(up == 1){
            randY = randint(0, randY);
        }else{
            randY = randint(randY, yDim-1);
        }
        if(left == 1){
            randX = randint(0, randX);
        }else{
            randX = randint(randX, xDim-1);
        }
    }
    vector<int> v = {randX,randY};
    cout<<"Done!"<<endl;
    return v;
    */
}

