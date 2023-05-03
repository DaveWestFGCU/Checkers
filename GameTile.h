#ifndef GAMETILE_H
#define GAMETILE_H

#include "Location.h"
#include "Man.h"
#include "King.h"

/**
 * A tile on the board. Can hold a Piece object.
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
    Man * getPiece() { return gamePiece; }
    bool hasPiece();
    std::string display();
    void removePiece();
};


GameTile::GameTile(int x, int y) {
    myLocation.setX(x);
    myLocation.setY(y);
}


void GameTile::setPiece(Man * gamePiece) {
    this-> gamePiece = gamePiece;
    tileFilled = true;
}


bool GameTile::hasPiece() {
    return tileFilled;
}


std::string GameTile::display() {
    if (tileFilled) {
        return gamePiece->getSymbol();
    }

    return "___";     // empty tile space
}


void GameTile::removePiece() {
    gamePiece = nullptr;
    tileFilled = false;
}

#endif //GAMETILE_H
