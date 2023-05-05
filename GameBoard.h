#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <windows.h>
#include "GameTile.h"

const int PIECES_PER_PLAYER = 12;

/**
 * Class for a gameboard object.
 * Contains a 2d array of GameTile objects and an array of piece objects.
 */
class GameBoard {
protected:
    int xDimension;
    int yDimension;
    GameTile *** tileArray;
    Man * pieceArray[24];

public:
    GameBoard(int xDimension, int yDimension);

    void newBoard();
    void buildPieces();
    void display();
    void playTurn(int player);
    Location promptAndValidateLocation(std::string prompt);
    Location getPieceLocation(int player);
    Location getMove(int player, Location loc, bool & inAttack);
    void movePiece(Location prevLoc, Location newLoc);
    bool isLastRow(Location newLoc);
    void kingMe(Location newLoc);
    bool isGameOver(int opponent);
};


#endif //GAMEBOARD_H
