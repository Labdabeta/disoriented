#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include "mazegen.h"
using namespace std;

const int p1 = 1061;
const int p2 = 1361; // two large primes for new mazes every time
string str(int c); 
string pointToString(int x, int y){
    return str(x) + ","+str(y);
}
string str(int c){
    stringstream s;
    s << c;
    return s.str();
}
vector<int> range(int n){
    vector<int> v;
    for(int i=0;i<n;i++){
        v.push_back(i);
    }
    return v;
}
int randint(int low, int high){
    return (rand() % (high-low+1))+low;
}
bool has_key(unordered_map<string, int>map,string key){
    return map.find(key) == map.end();
}
int indexOf(vector<int> v, int n){
    vector<int>::iterator d =find(v.begin(), v.end(),n);
    if(d == v.end()){
        return -1;
    }
    return d-v.begin();
}

int indexOf(vector<wall> v, wall n){
    vector<wall>::iterator d =find(v.begin(), v.end(),n);
    if(d == v.end()){
        return -1;
    }
    return d-v.begin();
}

vector<wall> genMaze(int width, int height, float density){
    unordered_map<string, int> maze;
    for(int i=0;i<height;i++){
        maze["0,"+str(i)+",let"] = 1;
        maze[pointToString(width-1, i)+",right"]=1;
    }
    for(int i=0;i<width;i++){
        maze[str(i)+",0,up"]=1;
        maze[pointToString(i,height-1)+",down"]=1;
    }
    vector<wall> wallList;
    if(width <= 1 || height <= 1){
        return wallList;
    } else {
        string largerSize = width>height ? "width" : "height";
        if(largerSize == "width"){
            int wallLoc =(width==2 || width==3) ? 0 : randint(int(width*0.4), int(width*0.6));
            vector<int> holes;
            int maxHoles = ceil(height*density);
            if(maxHoles <= 0){
                maxHoles = 1;
            }
            int newHole;
            for(int i=0;i<maxHoles;i++){
                newHole = -1;
                while(newHole == -1 || indexOf(holes, newHole) != -1){
                    newHole=randint(0, height-1);
                }
                holes.push_back(newHole);
            }
            for(int i=0;i<height;i++){
                if(indexOf(holes, i) != -1){
                    continue;
                }
                wall wallCell = wall(wallLoc, i, "right");
                string wallStr = pointToString(wallLoc, i);
                wallList.push_back(wallCell);
                maze[pointToString(wallLoc,i) + "," + "right"] = 1;
                maze[str(wallLoc+1)+","+str(i)+",left"] = 1;
            }
            vector<wall> near = genMaze(wallLoc+1,height,density);
            vector<wall> far  = genMaze(width-wallLoc-1,height,density);
            
            
           // vector<wall> finalWall = near + wallList + map(lambda x:[x[0]+wallLoc+1,x[1],x[2]],far);
            near.insert(near.end(),wallList.begin(),wallList.end());
            for(int i=0; i<far.size();i++){
                wall thisWall = far[i];
                near.push_back(wall(thisWall.x+wallLoc+1,thisWall.y,thisWall.dir));
            }
            return near;
            
        } else {
            int wallLoc =(height==2 || height==3) ? 0 : randint(int(height*0.4), int(height*0.6));
            vector<int> holes;
            int maxHoles = ceil(width*density);
            if(maxHoles <= 0){
                maxHoles = 1;
            }
            int newHole;
            for(int i=0;i<maxHoles;i++){
                newHole = -1;
                while(newHole == -1 || indexOf(holes, newHole) != -1){
                    newHole=randint(0, width-1);
                }
                holes.push_back(newHole);
            }
            for(int i=0;i<width;i++){
                if(indexOf(holes, i) != -1){
                    continue;
                }
                wall wallCell = wall(i,wallLoc, "down");
                string wallStr = pointToString(i,wallLoc);
                wallList.push_back(wallCell);
                maze[pointToString(i,wallLoc) + "," + "down"] = 1;
                maze[str(i)+","+str(wallLoc+1)+",up"] = 1;
            }
            vector<wall> near= genMaze(width, wallLoc+1, density);
            vector<wall> far = genMaze(width, height-wallLoc-1, density);
            near.insert(near.end(),wallList.begin(),wallList.end());
            for(int i=0; i<far.size();i++){
                wall thisWall = far[i];
                near.push_back(wall(thisWall.x,thisWall.y+wallLoc+1,thisWall.dir));
            }
            return near;
        }
        
    }
}
