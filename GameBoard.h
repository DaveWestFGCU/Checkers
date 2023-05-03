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
            tileArray[x][y] = new GameTile(x,y);
        }
    }
}   // end GameBoard(x, y) constructor


/**
 * Builds an array of pieces.
 */
void GameBoard::buildPieces() {
    for (int player = 0; player < 2; ++player) {
        for (int piece = 0; piece < PIECES_PER_PLAYER; ++piece) {
            int pieceIndex = (player * PIECES_PER_PLAYER) + (piece);
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

    // Checkers: Pieces on every other space.
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
    // Checkers: Pieces on every other space.
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
    // Highest row at top
    for (int y = yDimension-1; y >= 0; --y) {
        std::cout << y+1 << " ";
        // Lowest row on left
        for (int x = 0; x < xDimension; ++x) {
            std::cout << tileArray[x][y]->display();
        }
        std::cout << std::endl;
        Sleep(5);
    }
    std::cout << "   A  B  C  D  E  F  G  H" << std::endl;
}   // end display()


/**
 * Perform one player's game round
 * @param player - int specifier of which player
 */
void GameBoard::playTurn(int player) {
    bool inTurn = true;
    bool inAttack = false;
    Location pieceLoc, newLoc;

    while ( inTurn ) {
        // Force player to move same piece if making second move after jumping
        if ( !inAttack )
            pieceLoc = getPieceLocation(player);
        else {
            std::cout << "Player " << player
                      << " - You jumped a piece. Move again." << std::endl;
            pieceLoc = newLoc;
        }

        try {   // Make a move
            newLoc = getMove(player, pieceLoc, inAttack);
            movePiece(pieceLoc, newLoc);

            // Check if piece can be upgraded
            if ( isLastRow( newLoc ) ) {
                kingMe( newLoc );
            }

            if (!inAttack)
                return;     // Turn is over
        }
        catch ( std::string error ) {
            if ( error == "back" && !inAttack ) {       // Player changed mind about piece to move.
                continue;           // Restart turn.
            }
            if ( error == "end" && !inAttack ) {        // Attempts to end turn before first move
                std::cout << "Unable to end turn. Please move a piece." << std::endl;
            }
            if ( error == "back" && inAttack ) {         // Attempts to change piece after jumping
                std::cout << "Unable to go back to piece selection." << std::endl;
            }
            if ( error == "end" && inAttack ) {         // Wants to end turn after jumping
                system("cls");
                display();
                return;
            }
        } // end catch
    }   // end while ( inTurn )
}   // end PlayTurn()


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

        if (locationInputString == "back" ||
            locationInputString == "Back" ||
            locationInputString == "BACK")  {
            std::string throwString = "back";
            throw throwString;
        }

        if (locationInputString == "end" ||
            locationInputString == "End" ||
            locationInputString == "END") {
            std::string throwString = "end";
            throw throwString;
        }

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
Location GameBoard::getPieceLocation(int player) {
    bool validInput = false;
    Location loc;

    while ( !validInput ) {
        std::string piecePrompt = "Player " + std::to_string(player)
                                  +" - Choose your piece: ";

        loc = promptAndValidateLocation(piecePrompt);

        if (tileArray[loc.getX()][loc.getY()] -> hasPiece()) {
            if (tileArray[loc.getX()][loc.getY()] -> getPiece() -> getPlayer() == player) {
                validInput = true;
            } else
                std::cout << "This "
                          << tileArray[loc.getX()][loc.getY()] -> getPiece() -> getName()
                          << " is not yours! Please try again." << std::endl;
        } else
            std::cout << "No piece was found at this spot. Please try again."
                      << std::endl;
    }

    return loc;
} // end getPieceLocation()


/**
 * Prompts player for where they want to move their piece with input validation.
 * Determines whether move is a movement or attack.
 * If attack, removes opponent's captured piece.
 * @param player - int: Specifier for which player
 * @param loc - Location of piece to move
 * @param inAttack - & bool: true if move fits attack criteria and captures opponent's piece
 * @return New location to move player's piece
 */
Location GameBoard::getMove(int player, Location loc, bool & inAttack) {
    bool validInput = false;
    Location newLoc;
    while ( !validInput ) {
        std::string movePrompt = "Player " + std::to_string(player)
                                 + " - Where would you like to move your "
                                 + tileArray[loc.getX()][loc.getY()]->getPiece()->getName()
                                 + "?\n";
        if ( !inAttack )
            movePrompt += "(or type 'back' to change your piece): ";
        else
            movePrompt += "(or type 'end' to end your turn): ";

        // Loop until a position on the board is given
        newLoc = promptAndValidateLocation(movePrompt);

        // Check if it's a valid move
        bool moveIsValid = tileArray[loc.getX()][loc.getY()]-> getPiece()-> validMove(newLoc);
        if ( !inAttack && moveIsValid ) {
            if ( tileArray[newLoc.getX()][newLoc.getY()] -> hasPiece() ) {
                std::cout << "There is a piece at this location. Please try again."
                          << std::endl;
            }
            else {
                validInput = true;
            }
        }
        else {  // Not valid move, but maybe valid attack
            if (tileArray[loc.getX()][loc.getY()] -> getPiece() -> validAttack(newLoc) ) {
                if ( tileArray[newLoc.getX()][newLoc.getY()] -> hasPiece() ) {
                    std::cout << "There is a piece at this location. Please try again."
                              << std::endl;
                }
                else {
                    // Use midpoint formula to check for piece to jump.
                    Location midLoc = ((newLoc + loc) / 2);
                    GameTile * tileToJump = tileArray[midLoc.getX()][midLoc.getY()];
                    if ( tileToJump-> hasPiece()) {
                        if ( tileToJump-> getPiece() -> getPlayer() == player ) {
                            std::cout << "You cannot capture your own piece. Please try again."
                                      << std::endl;
                        }
                        else {
                            validInput = true;
                            inAttack = true;
                            tileToJump->getPiece()->capture();
                            tileToJump->removePiece();
                        }
                    } else
                        std::cout << "This move is invalid. Please try again."
                                  << std::endl;
                }
            }
            else
                std::cout << "This move is invalid. Please try again."
                          << std::endl;
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
    // update piece location
    tileArray[prevLoc.getX()][prevLoc.getY()] -> getPiece() -> move(newLoc);

    // update board tiles
    delete tileArray[newLoc.getX()][newLoc.getY()];
    tileArray[newLoc.getX()][newLoc.getY()] = tileArray[prevLoc.getX()][prevLoc.getY()];
    tileArray[prevLoc.getX()][prevLoc.getY()] = new GameTile();

    system("cls");
    display();
}


bool GameBoard::isLastRow(Location newLoc) {
    return newLoc.getY() == 0 || newLoc.getY() == yDimension-1;
}


void GameBoard::kingMe(Location newLoc) {
    tileArray[newLoc.getX()][newLoc.getY()] -> getPiece() -> kingMe();
    system("cls");
    display();

    std::cout << "Your man is now a king!" << std::endl;
}


/**
 * Checks if game over conditions are met.
 * (i.e. all of opponents pieces are captured)
 * @param opponent - int: player identifier for the other player
 * @return True if game over conditions are met
 */
bool GameBoard::isGameOver( int opponent ) {
    for (int piece = 0; piece < PIECES_PER_PLAYER; ++piece) {
        int pieceIndex = (opponent * PIECES_PER_PLAYER) + piece;

        if ( pieceArray[pieceIndex]-> inPlay() ) {
            return false;
        }
    }

    return true;
}


#endif //GAMEBOARD_H
