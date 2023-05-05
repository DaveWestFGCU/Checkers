#ifndef PIECE_H
#define PIECE_H

#include <iostream>
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
    Location myLocation;    // TODO : Move location out of piece/man/king
    bool alive = true;

public:
    // Constructors
    Piece () = default;
    Piece (int player);
    ~Piece () = default;

    // Single line functions
    std::string getSymbol();
    int getPlayer();
    std::string getName();
    void updatePosition(Location newLocation);
    Location getLocation();
    bool inPlay();
    void capture();

    // 2+ line functions
    void move(Location newLoc);
    void release(Location newLoc);

    // Virtual functions
    virtual bool validMove(Location newLoc) = 0;
    virtual bool validAttack(Location newLoc) = 0;
};



#endif //PIECE_H
