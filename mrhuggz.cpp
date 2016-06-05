#include "mrhuggz.h"
#include <math.h>

bool collision(int radius, int centerX, int centerY, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
    //just touching does not count as collision
    //check top side
    int disc = -topLeftY*topLeftY + 2*centerY*topLeftY + radius*radius - centerY*centerY;
    if(disc >= 0){ // check collision
        float point1 = centerX - sqrt(disc);
        float point2 = centerX + sqrt(disc);
        if (point1 < bottomRightX && point1 > topLeftX) {
            return true;
        }
        if (point2 < bottomRightX && point2 > topLeftX) {
            return true;
        }
    }
    //check bottom side
    disc = -bottomRightY*bottomRightY + 2*centerY*bottomRightY + radius*radius - centerY*centerY;
    if(disc >= 0){ // check collision
        float point1 = centerX - sqrt(disc);
        float point2 = centerX + sqrt(disc);
        if (point1 < bottomRightX && point1 > topLeftX) {
            return true;
        }
        if (point2 < bottomRightX && point2 > topLeftX) {
            return true;
        }
    }
    //check left side
    disc = -topLeftX*topLeftX + 2*centerX*topLeftX+radius*radius - centerX*centerX;
    if(disc >= 0){ // check collision
        float point1 = centerY - sqrt(disc);
        float point2 = centerY + sqrt(disc);
        if (point1 < bottomRightY && point1 > topLeftY) {
            return true;
        }
        if (point2 < bottomRightY && point2 > topLeftY) {
            return true;
        }
    }    
    //check right side
    disc = -bottomRightX*bottomRightX + 2*centerX*bottomRightX+radius*radius - centerX*centerX;
    if(disc >= 0){ // check collision
        float point1 = centerY - sqrt(disc);
        float point2 = centerY + sqrt(disc);
        if (point1 < bottomRightY && point1 > topLeftY) {
            return true;
        }
        if (point2 < bottomRightY && point2 > topLeftY) {
            return true;
        }
    }     
    return false;
}

