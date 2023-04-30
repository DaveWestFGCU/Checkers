#ifndef CHECKERS_PIECE_H
#define CHECKERS_PIECE_H

#include <string>
#include "Location.h"

/**
 * Class for a game piece object on a 2d board.
 */
class Piece {
protected:
    int player;
    std::string name;
    std::string symbol;
    Location loc;
    bool alive = true;

public:
    // Constructors
    Piece () = default;
    Piece (int player);
    ~Piece () { std::cout << "Piece destructor called" << std::endl;   }

    // One line functions
    std::string getSymbol() { return symbol; }
    int getPlayer() { return player; }
    std::string getName() { return name; }
    void updatePosition(Location newLocation) { loc = newLocation; }
    bool inPlay() { return alive; }
    void capture() { alive = false; }

    // Complex functions
    void move(Location newLoc);
    void release(Location newLoc);

    // Virtual functions
    virtual bool validMove(Location newLoc) = 0;
    virtual bool validAttack(Location newLoc) = 0;
};


Piece::Piece (int player) {
    this -> player = player;
    this -> symbol = "(" + std::to_string(player) + ")";
}


void Piece::move(Location newLoc) {
    // Player made a basic move. No attacking.
    if ( validMove(newLoc) ) {
        loc.setX(newLoc.getX());
        loc.setY(newLoc.getY());

        return;
    }
}


void Piece::release(Location newLoc) {
    alive = true;
    loc = newLoc;
}


#endif //CHECKERS_PIECE_H
