#ifndef CHECKERS_LOCATION_H
#define CHECKERS_LOCATION_H

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
};


/**
 *
 * @param locTwo
 * @return
 */
Location Location::operator+(Location locTwo) {
    int xSum = xCoord + locTwo.xCoord;
    int ySum = yCoord + locTwo.yCoord;
    Location sumLoc(xSum, ySum);

    return sumLoc;
}


/**
 * Returns the difference between this location (minuend) and
 * a second location (subtrahend).
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
 * Used with - operator to find midpoints (i.e.: (locA + locB) / 2 ).
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

    if (fabs(xFrac) > 10e-7 || fabs(yFrac) > 10e-7) {
        std::cout << "!! WARNING !!\n"
                     "Location division did not yield an integer x and y coordinate! "
                     "The result was truncated!" << std::endl;
    }

    return divLoc;
}


#endif //CHECKERS_LOCATION_H
