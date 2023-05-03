#include <iostream>
#include "GameBoard.h"

// ---------------| Constants |-------------------
const int X_SIZE = 8;    // Width of the board
const int Y_SIZE = 8;    // Height of the board


int main() {
    GameBoard checkerBoard(X_SIZE, Y_SIZE);

    // Set initial game state
    checkerBoard.buildPieces();
    checkerBoard.newBoard();
    bool gameOver = false;
    int round { 0 };
    int player, opponent;

    system("cls");
    checkerBoard.display();

    // Play game
    while (!gameOver) {
        ++round;
        // Player 0 goes first
        player = (round - 1) % 2;
        checkerBoard.playTurn( player );

        opponent = (player + 1) % 2;
        gameOver = checkerBoard.isGameOver( opponent );
    }

    std::cout << "Player " << player << " wins!";

    return 0;
}
