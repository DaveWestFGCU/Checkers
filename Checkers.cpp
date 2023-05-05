#include "Checkers.h"

Checkers::Checkers() {
    checkerBoard = new GameBoard(BOARD_X_SIZE, BOARD_Y_SIZE);

    // Set initial game state
    checkerBoard -> buildPieces();
    checkerBoard -> newBoard();
    checkerBoard -> display();
}

void Checkers::play() {
    // Play game
    while (!gameOver) {
        ++round;
        // Player 0 goes first
        player = (round - 1) % 2;
        checkerBoard -> playTurn( player );

        opponent = (player + 1) % 2;
        gameOver = checkerBoard -> isGameOver( opponent );
    }

    std::cout << "Player " << player << " wins!";
}