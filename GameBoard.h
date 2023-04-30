#ifndef CHECKERS_GAMEBOARD_H
#define CHECKERS_GAMEBOARD_H

#include "GameTile.h"

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
    void getPiece(int player, Location & loc);
    Location getMove(int player, Location loc, bool &isAttack);
    void movePiece(Location prevLoc, Location newLoc);
};


/**
 * Constructs a new board.
 * @param xDimension Int: Number of tiles wide
 * @param yDimension Int: Number of tiles tall
 */
GameBoard::GameBoard(int xDimension, int yDimension) {
    this -> xDimension = xDimension;
    this -> yDimension = yDimension;

    tileArray = new GameTile**[xDimension];

    for (int x = 0; x < xDimension; ++x) {
        tileArray[x] = new GameTile *[yDimension];

        for (int y = 0; y < yDimension; ++y) {
            tileArray[x][y] = new GameTile();
        }
    }
}   // end GameBoard(xDimension, yDimension) constructor


/**
 * Builds an array of pieces.
 */
void GameBoard::buildPieces() {
    for (int player = 0; player < 2; ++player) {
        for (int piece = 0; piece < 12; ++piece) {
            int pieceIndex = (player * 12)+(piece);
            pieceArray[pieceIndex] = new Man(player);
        }
    }
}


/**
 * Starts a new board with initial game conditions.
 */
void GameBoard::newBoard() {
    // Set up close side of board (player 0)
    int thisPiece { 0 };

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < xDimension; ++x) {
            if ( !((x + y) % 2)) {
                // Add piece to tile
                tileArray[x][y]->setPiece( pieceArray[thisPiece] );

                // Set piece location
                Location newPos(x,y);
                pieceArray[thisPiece] -> updatePosition(newPos);
                ++thisPiece;
            }
        }
    }

    // Set up far side of board (player 1)
    for (int y = yDimension-3; y < yDimension; ++y) {
        for (int x = 0; x < xDimension; ++x) {
            if (!((x + y) % 2)) {
                // Add piece to tile
                tileArray[x][y]->setPiece( pieceArray[thisPiece] );

                // Set piece location
                Location newPos(x,y);
                pieceArray[thisPiece] -> updatePosition(newPos);
                ++thisPiece;
            }
        }
    }
}   // end newBoard()


/**
 * Prints a representation of the game board to console.
 */
void GameBoard::display() {
    for (int y = yDimension-1; y >= 0; --y) {
        std::cout << y+1 << " |";
        for (int x = 0; x < xDimension; ++x) {
            std::cout << "";
            std::cout << tileArray[x][y]->display();
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "    A   B   C   D   E   F   G   H" << std::endl;
}   // end display()


/**
 * Perform one player's game round
 * @param player - int specifier of which player
 */
void GameBoard::playTurn(int player) {
    system("cls");
    display();

    bool isAttack = false;

    Location loc, newLoc;
    getPiece(player, loc);
    newLoc = getMove(player, loc, isAttack);
    movePiece(loc, newLoc);
    std::cout << "You jumped your opponent's piece!" << std::endl;
//    while (isAttack) {
//        // continue jumping
//    }
}


/**
 * Checks that the input location is on the game board.
 * Loops until valid input is provided.
 * Sets passed-by-reference x and y coordinates.
 * @param prompt String -> Text to use for user prompt.
  * @return Location -> An input validated location on the game board.
  */
Location GameBoard::promptAndValidateLocation(std::string prompt) {
    bool inputOnBoard = false;
    Location loc;

    while ( !inputOnBoard ) {
        std::cout << prompt;
        std::string locationInputString;
        std::cin >> locationInputString;

        loc.setX( (int)locationInputString[0] - 65 );
        loc.setY( (int)locationInputString[1] - 49 );

        bool xOnBoard = false;
        bool yOnBoard = false;

        // Input validation: X-coordinate
        if (loc.getX() >= 0 && loc.getX() < xDimension) {
            xOnBoard = true;
        } else {
            loc.setX(loc.getX() - 31);
            if (loc.getX() > 0 && loc.getX() < xDimension) {
                xOnBoard = true;
            }
        }

        //Input validation: Y-coordinate
        if (loc.getY() > -1 && loc.getY() < yDimension) {
            yOnBoard = true;
        }

        if (!xOnBoard || !yOnBoard)
            std::cout << "This is not a valid tile! Please try again." << std::endl;
        else
            inputOnBoard = true;
    }
    return loc;
}


/**
 * Checks if a valid piece is in the location provided
 * @return
 */
void GameBoard::getPiece(int player, Location & loc) {
    bool validInput = false;

    while ( !validInput ) {
        std::string piecePrompt = "Player " + std::to_string(player)
                                  +" - Choose your piece: ";
        loc = promptAndValidateLocation(piecePrompt);

        if (tileArray[loc.getX()][loc.getY()]->hasPiece()) {
            if (tileArray[loc.getX()][loc.getY()]->getPiece()->getPlayer() == player) {
                validInput = true;
            } else
                std::cout << "This "
                          << tileArray[loc.getX()][loc.getY()]->getPiece()->getName()
                          << " is not yours! Please try again." << std::endl;
        } else
            std::cout << "No piece was found at this spot. Please try again."
                      << std::endl;
    }
} // end getPiece()


/**
 * Prompts player for where they want to move their piece with input validation.
 * Determines whether move is a movement or attack.
 * If attack, removes opponent's captured piece.
 * @param player - int: Specifier for which player
 * @param loc - Location of piece to move
 * @param isAttack - & bool: true if move fits attack criteria and captures opponent's piece
 * @return New location to move player's piece
 */
Location GameBoard::getMove(int player, Location loc, bool &isAttack) {
    bool validInput = false;
    bool maybeValid = false;
    Location newLoc;
    while ( !validInput ) {
        std::string movePrompt = "Player " + std::to_string(player)
                                 + " - Where would you like to move your "
                                 + tileArray[loc.getX()][loc.getY()]->getPiece()->getName()
                                 + "? ";
        newLoc = promptAndValidateLocation(movePrompt);

        // Check if it's a valid move
        if ( tileArray[loc.getX()][loc.getY()] -> getPiece() -> validMove(newLoc) ) {
            if (tileArray[newLoc.getX()][newLoc.getY()] -> hasPiece() == false ) {
                validInput = true;
            }
            else {
                std::cout << "You already have a piece at this location. Please try again."
                          << std::endl;
            }
        }
        else {  // Not valid move, but maybe valid attack
            if ( tileArray[loc.getX()][loc.getY()] -> getPiece() -> validAttack(newLoc)) {
                // Use midpoint formula to check for piece to jump.
                Location midLoc = ((newLoc + loc) / 2);
                if (tileArray[midLoc.getX()][midLoc.getY()] -> hasPiece()) {
                    validInput = true;
                    isAttack = true;
                    tileArray[midLoc.getX()][midLoc.getY()] -> getPiece() -> capture();
                    tileArray[midLoc.getX()][midLoc.getY()] -> removePiece();
                }
            }
            else
                std::cout << "This move is invalid. Please try again." << std::endl;
        }
    }
    return newLoc;
}   // end getMove()

/**
 * Moves player's piece to new location.
 * @param prevLoc Location: Start point for player's move
 * @param newLoc Location: End point for player's move
 */
void GameBoard::movePiece(Location prevLoc, Location newLoc) {
    // update piece
    tileArray[prevLoc.getX()][prevLoc.getY()] -> getPiece() -> move(newLoc);

    // update board tiles
    delete tileArray[newLoc.getX()][newLoc.getY()];
    tileArray[newLoc.getX()][newLoc.getY()] = tileArray[prevLoc.getX()][prevLoc.getY()];
    tileArray[prevLoc.getX()][prevLoc.getY()] = new GameTile();

}

#endif //CHECKERS_GAMEBOARD_H
