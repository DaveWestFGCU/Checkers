#include "GameTile.h"


GameTile::GameTile(int x, int y) {
    myLocation.setX(x);
    myLocation.setY(y);
}


void GameTile::setPiece(Man * gamePiece) {
    this-> gamePiece = gamePiece;
    tileFilled = true;
}

Man * GameTile::getPiece() {
    return gamePiece;
}

bool GameTile::hasPiece() {
    return tileFilled;
}


std::string GameTile::display() {
    if (tileFilled) {
        return gamePiece->getSymbol();
    }

    char whiteSpace = (char)178;    //ASCII for ▓
    std::string whiteTile(1,whiteSpace);
    whiteTile += whiteSpace;
    whiteTile += whiteSpace;

    if ( (myLocation.getX() + myLocation.getY()) % 2 )
        return whiteTile;

    return "   ";     // empty tile space
}


void GameTile::removePiece() {
    gamePiece = nullptr;
    tileFilled = false;
}

