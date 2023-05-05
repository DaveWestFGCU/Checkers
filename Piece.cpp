#include "Piece.h"


Piece::Piece (int player) {
    this -> player = player;
    this -> symbol = "(" + std::to_string(player) + ")";
}


std::string Piece::getSymbol() {
    return symbol;
}


int Piece::getPlayer() {
    return player;
}


std::string Piece::getName() {
    return name;
}


void Piece::updatePosition(Location newLocation) {
    myLocation = newLocation;
}


Location Piece::getLocation() {
    return myLocation;
}


bool Piece::inPlay() {
    return alive;
}


void Piece::capture() {
    alive = false;
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
