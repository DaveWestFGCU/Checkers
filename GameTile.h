#ifndef CHECKERS_GAMETILE_H
#define CHECKERS_GAMETILE_H

#include "Man.h"
#include "King.h"

/**
 * A tile on the board. Can hold a Piece object.
 */
class GameTile {
protected:
    Man * gamePiece = nullptr;
    bool tileFilled { false };

public:
    GameTile() = default;
    void setPiece(Man * gamePiece);
    Man * getPiece() { return gamePiece; }
    bool hasPiece();
    std::string display();
    void removePiece();
};


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

#endif //CHECKERS_GAMETILE_H
