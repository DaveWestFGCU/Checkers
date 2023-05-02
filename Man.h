#ifndef CHECKERS_MAN_H
#define CHECKERS_MAN_H

#include "Piece.h"
#include "King.h"

class Man : virtual public Piece, public King {
protected:
    bool isKing = false;

public:
    Man() = default;
    Man(int player);
    ~Man() { std::cout << "Man destructor called." << std::endl;}

    bool validMove(Location newLoc);
    bool validAttack(Location newLoc);
    void kingMe();
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
    // Basic man movement
    if ( isKing )
        return validKingMove(newLoc);
    else {
        // Check if move is one space to left or right
        if ( newLoc.getX() == myLocation.getX() + 1 ||
             newLoc.getX() == myLocation.getX() - 1 ) {

            // Check if move is "forward", which depends on player
            if ( ( player == 0 && newLoc.getY() == myLocation.getY() + 1 ) ||
                 ( player == 1 && newLoc.getY() == myLocation.getY() - 1 ) )
                return true;
        }
    }
    return false;
}   // end validKingMove()


/**
 * Determines if a move attempt is a valid attacking move (moving 2 spots)
 * @param newLoc
 * @return
 */
bool Man::validAttack(Location newLoc) {
    // Jump movement
    if ( isKing )
        return validKingAttack(newLoc);
    else {
        // Check if move is two spaces to left or right
        if ( newLoc.getX() == myLocation.getX() + 2 ||
             newLoc.getX() == myLocation.getX() - 2 ) {

            // Check if move is "forward", which depends on player
            if ( player == 0 && newLoc.getY() == myLocation.getY() + 2 ||
                 player == 1 && newLoc.getY() == myLocation.getY() - 2 )
                return true;
        }
        return false;
    }

} // end validAttack()


/**
 * Turn man into king. Uses king class inheritance for moves and attacks.
 */
void Man::kingMe() {
    isKing = true;
    name = "king";
    symbol = "{" + std::to_string(player) + "}";
}


#endif //CHECKERS_MAN_H
