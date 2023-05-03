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
    Location(int x, int y) {
        xCoord = x;
        yCoord = y;
    }

    // Get Functions
    int getX() { return xCoord; }
    int getY() { return yCoord; }

    // Set Functions
    void setX(int newX) { xCoord = newX; }
    void setY(int newY) { yCoord = newY; }

    // Operator Overloading
    Location operator+(Location locTwo);
    Location operator-(Location locTwo);
    Location operator/(int divisor);
    Location operator=(Location locTwo);
};


/**
 * Addition operator. Adds the first Location and second Location's x and y coordinates.
 * Used in the midpoint formula (i.e.: (loc + locTwo) / 2 ).
 * @param locTwo - The location to become the second addend
 * @return Location - the sum of two locations
 */
Location Location::operator+(Location locTwo) {
    int xSum = xCoord + locTwo.xCoord;
    int ySum = yCoord + locTwo.yCoord;
    Location sumLoc(xSum, ySum);

    return sumLoc;
}


/**
 * Subtraction operator. Subtracts this location (minuend) from a second location (subtrahend).
 * @param locTwo : Second location (subtrahend)
 * @return A Location of the distance between locations.
 */
Location Location::operator-(Location locTwo) {
    int xDiff = locTwo.getX() - xCoord;
    int yDiff = locTwo.getY() - yCoord;
    Location diffLoc(xDiff, yDiff);

    return diffLoc;
}

/**
 * Divides a location by an integer.
 * Used in midpoint formula (i.e.: (locA + locB) / 2 ).
 * @param divisor int: Should be a common factor between location xCoord and yCoord.
 * @return A Location with xCoord / divisor and yCoord / divisor.
 */
Location Location::operator/(int divisor) {
    double divX = xCoord / (double)divisor;
    double divY = yCoord / (double)divisor;

    Location divLoc((int)divX, (int)divY);

    // Game tiles are discrete, so check for fractions and warn if found
    double discardIntegral;
    double xFrac = std::modf(divX, &discardIntegral);
    double yFrac = std::modf(divY, &discardIntegral);

    // Make sure the fraction isn't due to double precision margin of error
    if (fabs(xFrac) > 10e-7 || fabs(yFrac) > 10e-7) {
        std::cout << "!! WARNING !!\n"
                     "Location division did not yield an integer x or y coordinate! "
                     "The result was truncated!" << std::endl;
    }

    return divLoc;
}


/**
 * Equality operator. Copies the x and y from the right of the operator to this
 * Location's xCoord and yCoord.
 * @param locTwo - Location to copy from.
 * @return This location.
 */
Location Location::operator=(Location locTwo) {
        xCoord = locTwo.getX();
        yCoord = locTwo.getY();

    return *this;
}

#endif //LOCATION_H
