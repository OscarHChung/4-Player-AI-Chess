#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <string>
#include <vector>
#include "piece.h"
#include "pawn.h"
#include "queen.h"
#include "bishop.h"
#include "king.h"
#include "rook.h"
#include "knight.h"
#include "empty.h"
#include "textdisplay.h"
#include "player.h"
#include "computer.h"
#include "graphicsdisplay.h"

using namespace std;


class Game{
    // Private Members
    std::vector<std::vector<Piece*>> board;
    const int gridSize = 8;
    TextDisplay *td;
    GraphicsDisplay *gd = nullptr;
    bool boardAlreadyInitalized = false; // To prevent deleting uninitialized pointers
    bool whiteGoesNext = true; // gameStart function may change this
    bool defaultBoard = true; // game gets constructed w/ default board, if false there is no en passant and castling
    bool enPassantAvailable = false; // this gets set to true for one turn after a pawn makes a two-square move
    int enPassantColumn = -1;
    string pawnPromotePiece; // Represents what piece the user wants their pawn to be promoted to
    bool cpuIsMoving = false; // When a cpu is moving, this is set to on so that user-error msgs don't print
    Player *whiteplayer = new Player('w', 0, false);
    Player *blackplayer = new Player ('b', 0, false);
    Player *wtemp = new Player('w', 0, false);
    Player *btemp = new Player('b', 0, false);


    // Converts tile notation to coord notation i.e. a2 --> 6,0
    int convertRow(string tile);
    int convertCol(string tile);

    // Converts coord notation to tile notation i.e. 6,0 --> a2
    std::string convertTile(int row, int col);

    //Checks if "colour" is in check
    bool inCheck(char colour);

    // Moves a piece to this spot to see if it puts king in check
    bool inCheckTest(int startRow, int startCol, int endRow, int endCol, char colour);

    // Moves a piece to this spot to see if it puts king in checkmate
    bool inCheckmateTest(int startRow, int startCol, int endRow, int endCol, char colour);

    // Generates legal moves to see if player can legally move a piece
    // true if there are legal moves, false if none
    bool generateLegalMoves(char colour);


  public:
    
    //Constructor Destructor
    Game();
    ~Game();

    //Public Functions
    bool move(string startTile, string endTile);
    void cpuMove();
    void makePlayer(char colour, bool isComputer, int level);
    void removePiece(string tile);
    void addPiece(string tile, char pieceLetter); 
    void clearBoard();
    void defaultSetup();
    bool isGameOver(); 
    void gameStart(bool whiteGoesNext);
    void pawnPromoteAttempt(string pieceLetter);
    bool getTurn(); // for resign in main to check who's turn it is
    Player& getPlayer(char colour); // get the player score
    Player& finalscore(char colour);
    
    // Makes a list of strings in the format "a1h8" for our computer to use
    // All the moves in this list are moves that prefers capturing moves and checks over other moves.
    std::vector<std::string> generateLegalMovesLevel2(char colour);

    // This function generates moves that should be avoided by the computer
    // It receives all the moves from level2moves and removes the undesriable moves
    std::vector<std::string> generateLegalMovesLevel3(char colour);

    // Uses level 3 pool of moves as starting point
    // Prioritizes checkmate moves, uneatable checks, multi-advantage moves, and orders priority of capture and capture avoidance based on piece type
    std::vector<std::string> generateLegalMovesLevel4(char colour);

    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
