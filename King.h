#ifndef CHECKERS_KING_H
#define CHECKERS_KING_H

#include "Piece.h"

class King : public Man {

public:
    King() = default;
    King(int player);
    ~King() { std::cout << "King destructor called." << std::endl;  }

    bool validMove(Location newLoc);
    bool validAttack(Location newLoc);
};


/**
 * Basic movement, determine whether move is valid
 * @param newX int -> new x coordinate
 * @param newY int -> new y coordinate
 * @return bool -> true if the move is valid
 */
bool King::validMove(Location newLoc) {
    // Check if move is one space to left or right
    if (newLoc.getX() == myLocation.getX() + 1 || newLoc.getX() == myLocation.getX() - 1 )
        // Check if move is one space forward or back
        if ( newLoc.getX() == myLocation.getY() + 1 || newLoc.getX() == myLocation.getY() - 1 )
            return true;

    return false;
}   // end validMove()

/**
 * Determines if a move attempt is a valid attacking move (moving 2 spots)
 * @param newLoc
 * @return
 */
bool King::validAttack(Location newLoc) {
    // Jump movement
    // Check if move is two spaces to left or right
    if ( newLoc.getX() == myLocation.getX() + 2 || newLoc.getX() == myLocation.getX() - 2 )
        // Check if move is two spaces forward or back
        if ( newLoc.getX() == myLocation.getY() + 2 || newLoc.getX() == myLocation.getY() - 2 )
            return true;

    return false;
}
#endif //CHECKERS_KING_H
