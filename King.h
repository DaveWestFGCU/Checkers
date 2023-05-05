#ifndef CHECKERS_KING_H
#define CHECKERS_KING_H

#include "Piece.h"

class King : virtual public Piece {

public:
    King() = default;
    ~King() = default;

    bool validKingMove(Location newLoc);
    bool validKingAttack(Location newLoc);
};


#endif //CHECKERS_KING_H
