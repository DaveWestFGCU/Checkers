#ifndef GAMETILE_H
#define GAMETILE_H

#include "Location.h"
#include "Man.h"
#include "King.h"


/**
 * A tile on the board. Holds a pointer to the piece on it.
 */
class GameTile {
protected:
    Man * gamePiece = nullptr;
    bool tileFilled { false };
    Location myLocation;

public:
    GameTile() = default;
    GameTile(int x, int y);
    void setPiece(Man * gamePiece);
    Man * getPiece();
    bool hasPiece();
    std::string display();
    void removePiece();
};


#endif //GAMETILE_H
