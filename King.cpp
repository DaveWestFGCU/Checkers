#include "King.h"


/**
 * Basic movement, determine whether move is valid
 * @param newX int -> new x coordinate
 * @param newY int -> new y coordinate
 * @return bool -> true if the move is valid
 */
bool King::validKingMove(Location newLoc) {
    // Check if move is one space to left or right
    if ( newLoc.getX() == myLocation.getX() + 1 ||
         newLoc.getX() == myLocation.getX() - 1 )
        // Check if move is one space forward or back
        if ( newLoc.getY() == myLocation.getY() + 1 ||
             newLoc.getY() == myLocation.getY() - 1 )
            return true;

    return false;
}   // end validKingMove()

/**
 * Determines if a move attempt is a valid attacking move (moving 2 spots)
 * @param newLoc
 * @return
 */
bool King::validKingAttack(Location newLoc) {
    // Jump movement
    // Check if move is two spaces to left or right
    if ( newLoc.getX() == myLocation.getX() + 2 ||
         newLoc.getX() == myLocation.getX() - 2 )
        // Check if move is two spaces forward or back
        if ( newLoc.getY() == myLocation.getY() + 2 ||
             newLoc.getY() == myLocation.getY() - 2 )
            return true;

    return false;
}