#ifndef CHECKERS_MAN_H
#define CHECKERS_MAN_H

#include "King.h"
#include "Piece.h"


class Man : virtual public Piece, public King {
protected:
    bool isKing = false;

public:
    Man() = default;
    Man(int player);
    ~Man() = default;

    bool validMove(Location newLoc);
    bool validAttack(Location newLoc);
    void kingMe();
};


#endif //CHECKERS_MAN_H
