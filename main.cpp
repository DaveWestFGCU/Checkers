#include <iostream>
#include "GameBoard.h"

// ---------------| Constants |-------------------
const int xSize = 8;    // Width of the board
const int ySize = 8;    // Height of the board


int main() {
    GameBoard checkerBoard(xSize, ySize);

    // Set initial game state
    checkerBoard.buildPieces();
    checkerBoard.newBoard();
    bool gameOver = false;

   // system("cls");
    checkerBoard.display();

    // Play game
    while (!gameOver) {
            checkerBoard.playTurn(0);
            checkerBoard.playTurn(1);
    }


    return 0;
}
