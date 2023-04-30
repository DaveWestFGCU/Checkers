#ifndef CHECKERS_MAN_H
#define CHECKERS_MAN_H

#include "Piece.h"

class Man : public Piece {

public:
    Man() = default;
    Man(int player);
    ~Man() { std::cout << "Man destructor called." << std::endl;}

    bool validMove(Location newLoc);
    bool validAttack(Location newLoc);
};


Man::Man (int player) {
    name = "man";
    this -> player = player;
    symbol = "(" + std::to_string(player) + ")";
}


/**
 * Determines if the piece is moving as it should
 * @param newX int -> new x coordinate
 * @param newY int -> new y coordinate
 * @return bool -> true if the move is valid
 */
bool Man::validMove(Location newLoc) {
    // Basic movement
        // Check if move is one space to left or right
    if ( newLoc.getX() == loc.getX() + 1 || newLoc.getX() == loc.getX() - 1 ) {

        // Check if move is "forward", which depends on player
        if (player == 0 && newLoc.getY() == loc.getY() + 1)
            return true;

        if (player == 1 && newLoc.getY() == loc.getY() - 1)
            return true;
    }

    return false;
}   // end validMove()

/**
 * Determines if a move attempt is a valid attacking move (moving 2 spots)
 * @param newLoc
 * @return
 */
bool Man::validAttack(Location newLoc) {
    // Jump movement
    // Check if move is two spaces to left or right
    if ( newLoc.getX() == loc.getX() + 2 || newLoc.getX() == loc.getX() - 2 ) {
        // Check if move is "forward", which depends on player
        if (player == 0 && newLoc.getY() == loc.getY() + 2)
            return true;

        if (player == 1 && newLoc.getY() == loc.getY() - 2)
            return true;
    }
    return false;
}
#endif //CHECKERS_MAN_H
