#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <cmath>

class Location {
protected:
    int xCoord;
    int yCoord;

public:
    Location() = default;
    Location(int x, int y);

    // Get Functions
    int getX();
    int getY();

    // Set Functions
    void setX(int newX);
    void setY(int newY);

    // Operator Overloading
    Location operator+(Location locTwo);
    Location operator-(Location locTwo);
    Location operator/(int divisor);
    Location operator=(Location locTwo);
};


#endif //LOCATION_H
