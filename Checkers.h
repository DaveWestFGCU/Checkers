#ifndef CHECKERS_H
#define CHECKERS_H

#include "GameBoard.h"

// ----------------------| Constants |----------------------
const int BOARD_X_SIZE = 8;     // Tile width of a checkers board
const int BOARD_Y_SIZE = 8;     // Tile height of a checkers board


class Checkers {
protected:
    GameBoard * checkerBoard;
    bool gameOver = false;
    int round { 0 };
    int player, opponent;

public:
    Checkers();
    ~Checkers() = default;

    void play();
};


#endif //CHECKERS_H
