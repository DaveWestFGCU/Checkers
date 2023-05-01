#ifndef CHECKERS_KING_H
#define CHECKERS_KING_H

#include "Man.h"

class King : public Man {

public:
    King() = default;
    King(int player);
    ~King() { std::cout << "King destructor called." << std::endl;  }

    bool validMove(Location newLoc);
};


/**
 * Determines if the piece is moving as it should
 * @param newX int -> new x coordinate
 * @param newY int -> new y coordinate
 * @return bool -> true if the move is valid
 */
bool King::validMove(Location newLoc) {
    // Basic movement
    // Check if move is one space to left or right
    if (newLoc.getX() == myLocation.getX() + 1 || newLoc.getX() == myLocation.getX() - 1 ) {

        // Check if move is "forward", which depends on player
        if (player == 0 && newLoc.getY() == myLocation.getY() + 1)
            return true;

        if (player == 1 && newLoc.getY() == myLocation.getY() - 1)
            return true;
    }

    return false;
}   // end validMove()


#endif //CHECKERS_KING_H
