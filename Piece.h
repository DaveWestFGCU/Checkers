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
    Location myLocation;
    bool alive = true;

public:
    // Constructors
    Piece () = default;
    Piece (int player);
    ~Piece () { std::cout << "Piece destructor called" << std::endl;   }

    // Single line functions
    std::string getSymbol() { return symbol; }
    int getPlayer() { return player; }
    std::string getName() { return name; }
    void updatePosition(Location newLocation) { myLocation = newLocation; }
    Location getLocation() { return myLocation; }
    bool inPlay() { return alive; }
    void capture() { alive = false; }

    // 2+ line functions
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
    if ( validMove(newLoc) || validAttack(newLoc)) {
        myLocation.setX(newLoc.getX());
        myLocation.setY(newLoc.getY());
    }
    else
        std::cout << "Piece Move function failed!" << std::endl;
}


void Piece::release(Location newLoc) {
    alive = true;
    myLocation = newLoc;
}


#endif //CHECKERS_PIECE_H
