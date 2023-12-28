#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "player.h"

using namespace std;

// Start of PRIVATE FUNCTIONS 


int Game::convertRow(string tile){
    if (tile[1] == '8') return 0;
    else if (tile[1] == '7') return 1;
    else if (tile[1] == '6') return 2;
    else if (tile[1] == '5') return 3;
    else if (tile[1] == '4') return 4;
    else if (tile[1] == '3') return 5;
    else if (tile[1] == '2') return 6;
    else if (tile[1] == '1') return 7;
    else return -1; // Never gets called
}

int Game::convertCol(string tile){
    if (tile[0] == 'a') return 0;
    else if (tile[0] == 'b') return 1; 
    else if (tile[0] == 'c') return 2; 
    else if (tile[0] == 'd') return 3; 
    else if (tile[0] == 'e') return 4; 
    else if (tile[0] == 'f') return 5; 
    else if (tile[0] == 'g') return 6; 
    else if (tile[0] == 'h') return 7;
    else return -1;  // Never gets called
}

std::string Game::convertTile(int row, int col){
    string tile = "xx"; // placeholder text
    if (col == 0) tile[0] = 'a';
    else if (col == 1) tile[0] = 'b';
    else if (col == 2) tile[0] = 'c';
    else if (col == 3) tile[0] = 'd';
    else if (col == 4) tile[0] = 'e';
    else if (col == 5) tile[0] = 'f';
    else if (col == 6) tile[0] = 'g';
    else if (col == 7) tile[0] = 'h';
    if (row == 0) tile[1] = '8';
    else if (row == 1) tile[1] = '7';
    else if (row == 2) tile[1] = '6';
    else if (row == 3) tile[1] = '5';
    else if (row == 4) tile[1] = '4';
    else if (row == 5) tile[1] = '3';
    else if (row == 6) tile[1] = '2';
    else if (row == 7) tile[1] = '1';
    return tile;
}

bool Game::inCheck(char colour){ 
    char otherColour;
    if (colour == 'w') otherColour = 'b';
    else otherColour = 'w';

    // Find the King on the board
    int kingRow = -1;
    int kingCol = -1;
    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            if (board[row][col]->getType() == 'k' && board[row][col]->getColour() == colour){
                kingCol = col;
                kingRow = row;
            }
        }
    }

    // Check if other player pieces can take the King
    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            if (board[row][col]->getColour() == otherColour){
                if (board[row][col]->canMove(kingRow, kingCol)) return true;
            }
        }
    }

    return false;
}

bool Game::inCheckTest(int startRow, int startCol, int endRow, int endCol, char colour){

    
    Piece* temp = board[endRow][endCol];
    board[endRow][endCol] = board[startRow][startCol]; // making a dummy move
    board[endRow][endCol]->setRow(endRow);
    board[endRow][endCol]->setCol(endCol);
    board[startRow][startCol] = new Empty(startRow, startCol, board);
    bool moveLeadsToCheck = inCheck(colour);
    delete board[startRow][startCol]; // undo the dummy move
    board[startRow][startCol] = board[endRow][endCol];
    board[startRow][startCol]->setRow(startRow);
    board[startRow][startCol]->setCol(startCol);
    board[endRow][endCol] = temp;
    return moveLeadsToCheck;

}

bool Game::inCheckmateTest(int startRow, int startCol, int endRow, int endCol, char colour){

    Piece* temp = board[endRow][endCol];
    board[endRow][endCol] = board[startRow][startCol]; // making a dummy move
    board[startRow][startCol] = new Empty(startRow, startCol, board);

    bool moveLeadsToCheck = inCheck(colour);
    bool noRemainingMoves = !generateLegalMoves(colour);

    delete board[startRow][startCol]; // undo the dummy move
    board[startRow][startCol] = board[endRow][endCol];
    board[endRow][endCol] = temp;

    return (moveLeadsToCheck && noRemainingMoves);

}

// Determines if there exists legal moves for the given color
bool Game::generateLegalMoves(char colour){

    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            if (board[row][col]->getColour() == colour){ // First find a piece with the colour

                // Then, try to move this piece to every tile on the board
                for (int i = 0; i < gridSize; i++){
                    for (int j = 0; j < gridSize; j++){
                        if (board[row][col]->canMove(i, j)){

                            // Checking that this "legal" move doesn't put the king in check
                            bool moveLeadsToCheck = inCheckTest(row,col,i,j, board[row][col]->getColour());

                            // If this certain move can be made, return true aka there exists a legal move
                            if (!moveLeadsToCheck){
                                //cout << "A legal move: " << board[row][col]->getColour() << " " << board[row][col]->getType() << " from " << convertTile(row,col) << " to " << convertTile(i,j) << endl;
                                return true; 
                            } 

                        }

                    }
                }


            }
        }
    }
    return false;

}

// End of PRIVATE FUNCTIONS


// Start of PUBLIC FUNCTIONS

std::vector<std::string> Game::generateLegalMovesLevel2(char colour){

    std::vector<std::string> level2moves;

    char otherColour;
    if (colour == 'w') {
        otherColour = 'b';
    }
    else {
        otherColour = 'w';
    }

    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            if (board[row][col]->getColour() == colour){ // First find a piece with the colour

                // Then, try to move this piece to every tile on the board
                for (int i = 0; i < gridSize; i++){
                    for (int j = 0; j < gridSize; j++){
                        if (board[row][col]->canMove(i, j)){

                            // Checking that this "legal" move doesn't put the king in check
                            // If it does, this isn't a truly legal move so next iteration
                            bool moveLeadsToCheck = inCheckTest(row,col,i,j, colour);
                            if (moveLeadsToCheck) continue;

                            // If the move puts the other players king in check SET BOOL TO TRUE
                            // if the move CAPTURES the other other color SET BOOL TO TRUE
                            bool moveCausesCheck = inCheckTest(row,col,i,j, otherColour);
                            bool moveCaptures;
                            if (board[i][j]->getColour() == otherColour) moveCaptures = true;
                            else moveCaptures = false;

                            // If either bool is true, we add the move to the list
                            if (moveCausesCheck || moveCaptures){
                                string start = convertTile(row,col);
                                string end = convertTile(i,j);
                                string move = start + end;
                                level2moves.push_back(move);
                            }

                        }

                    }
                }


            }
        }
    }


    return level2moves;

}


// The goal of generateLegalMoves3 is to find all the moves that will put your player in a position of capture
std::vector<std::string> Game::generateLegalMovesLevel3(char colour){

    char otherColour;
    if (colour == 'w') otherColour = 'b';
    else otherColour = 'w';

    std::vector<std::string> movesToAvoid;

    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            if (board[row][col]->getColour() == colour){ // First find a piece with the colour

                // Then, try to move this piece to every tile on the board
                for (int i = 0; i < gridSize; i++){
                    for (int j = 0; j < gridSize; j++){
                        if (board[row][col]->canMove(i, j)){

                            // Checking that this "legal" move doesn't put the king in check
                            bool moveLeadsToCheck = inCheckTest(row,col,i,j, colour);
                            if (moveLeadsToCheck) continue; 
                            // Moves past this point are truly legal

                            // Update the board with our dummy move of our piece from row,col --> i,j s
                            Piece* temp = board[i][j];
                            board[i][j] = board[row][col]; 
                            board[i][j]->setRow(i);
                            board[i][j]->setCol(j);
                            board[row][col] = new Empty(row, col, board);

                            bool breakOut = false;

                            for (int otherColourRow = 0; otherColourRow < gridSize && !breakOut; otherColourRow++){
                                for (int otherColourCol = 0; otherColourCol < gridSize; otherColourCol++){
                                    if (board[otherColourRow][otherColourCol]->getColour() == otherColour && board[otherColourRow][otherColourCol]->canMove(i,j)){ 
                                        bool moveLeadsToCheckOtherColour = inCheckTest(otherColourRow,otherColourCol,i,j, otherColour);
                                        if (moveLeadsToCheckOtherColour) continue;
                                        
                                        
                                        string start = convertTile(row,col);
                                        string end = convertTile(i,j);
                                        string move = start + end;
                                        movesToAvoid.push_back(move);
                                        breakOut = true;
                                        break;
                                        

                                     }
                                }
                            }


                            delete board[row][col]; // undo the dummy move
                            board[row][col] = board[i][j];
                            board[row][col]->setRow(row);
                            board[row][col]->setCol(col);
                            board[i][j] = temp;

                        }

                    }
                }


            }
        }
    }
    std::vector<std::string> level2moves = generateLegalMovesLevel2(colour);
    std::vector<std::string> level3moves;

    for (auto &move2 : level2moves){
        bool foundInBoth = false;
        for (auto &badMove : movesToAvoid){
            if (move2 == badMove){
                foundInBoth = true;
                break;
            }
        }
        if (!foundInBoth) level3moves.push_back(move2);
    }

    return level3moves;

}

std::vector<std::string> Game::generateLegalMovesLevel4(char colour){

    std::vector<std::string> level4moves;

    char otherColour;
    if (colour == 'w') otherColour = 'b';
    else otherColour = 'w';

    // prioritize checkmate
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j]->getColour() == colour) {
                for (int a = 0; a < gridSize; ++a) {
                    for (int b = 0; b < gridSize; ++b) {
                        if (board[i][j]->canMove(a, b)) {
                            // ensuring legal move that won't cause self-check
                            bool moveLeadsToCheckOtherColour = inCheckTest(i, j, a, b, colour);
                            if (moveLeadsToCheckOtherColour) continue;

                            // check if move causes a checkmate for opponent
                            if (inCheckmateTest(i, j, a, b, otherColour)) {
                                level4moves.push_back(convertTile(i ,j) + convertTile(a, b));
                                return level4moves;
                            }
                        }
                    }
                }
            }
        }
    }

    // add safe checks
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j]->getColour() == colour) {
                // (a, b) is new square
                for (int a = 0; a < gridSize; ++a) {
                    for (int b = 0; b < gridSize; ++b) {
                        if (board[i][j]->canMove(a,b) && !inCheckTest(i, j, a, b, colour) && inCheckTest(i, j, a, b, otherColour)) {
                            // can move to (a, b) from (i, j)
                            // ensure new square movement is safe
                            bool safeCheck = true;

                            // checking for any opposing pieces attacking that square
                            // Update the board with our dummy move of our piece from row,col --> i,j s
                            Piece* temp = board[a][b];
                            board[a][b] = board[i][j]; 
                            board[a][b]->setRow(a);
                            board[a][b]->setCol(b);
                            board[i][j] = new Empty(i, j, board);

                            for (int c = 0; c < gridSize; ++c) {
                                for (int d = 0; d < gridSize; ++d) {
                                    if (board[c][d]->canMove(a, b) && !inCheckTest(c, d, a, b, otherColour)) {
                                        safeCheck = false;
                                    }
                                }
                            }
                        
                            delete board[i][j]; // undo the dummy move
                            board[i][j] = board[a][b];
                            board[i][j]->setRow(i);
                            board[i][j]->setCol(j);
                            board[a][b] = temp;

                            if (safeCheck) {
                                level4moves.push_back(convertTile(i, j) + convertTile(a, b));
                            }
                        }
                    }
                }
            }
        }
    }

    if (level4moves.size() != 0) {
        return level4moves;
    }

    // add safe captures
    // check for if it is a capture
    // (i ,j) is old square
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j]->getColour() == colour) {
                // (a, b) is new square
                for (int a = 0; a < gridSize; ++a) {
                    for (int b = 0; b< gridSize; ++b) {
                        if (board[a][b]->getColour() == otherColour && board[i][j]->canMove(a,b) && !inCheckTest(i, j, a, b, colour)) {
                            // ensure new square movement is safe
                            bool safeCapture = true;

                            // checking for any opposing pieces attacking that square
                            // Update the board with our dummy move of our piece from row,col --> i,j s
                            Piece* temp = board[a][b];
                            board[a][b] = board[i][j]; 
                            board[a][b]->setRow(a);
                            board[a][b]->setCol(b);
                            board[i][j] = new Empty(i, j, board);

                            for (int c = 0; c < gridSize; ++c) {
                                for (int d = 0; d < gridSize; ++d) {
                                    if (board[c][d]->canMove(a, b) && !inCheckTest(c, d, a, b, otherColour)) {
                                        safeCapture = false;
                                    }
                                }
                            }
                        
                            delete board[i][j]; // undo the dummy move
                            board[i][j] = board[a][b];
                            board[i][j]->setRow(i);
                            board[i][j]->setCol(j);
                            board[a][b] = temp;

                            if (safeCapture) {
                                level4moves.push_back(convertTile(i, j) + convertTile(a, b));
                            }
                        }
                    }
                }
            }
        }
    }

    if (level4moves.size() != 0) {
        return level4moves;
    }

    // add safe moves (general) if no other above options
    // (i ,j) is old square
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j]->getColour() == colour) {
                // (a, b) is new square
                for (int a = 0; a < gridSize; ++a) {
                    for (int b = 0; b< gridSize; ++b) {
                        if (board[i][j]->canMove(a,b) && !inCheckTest(i, j, a, b, colour)) {
                            // ensure new square movement is safe
                            bool safeMove = true;

                            // checking for any opposing pieces attacking that square
                            // Update the board with our dummy move of our piece from row,col --> i,j s
                            Piece* temp = board[a][b];
                            board[a][b] = board[i][j]; 
                            board[a][b]->setRow(a);
                            board[a][b]->setCol(b);
                            board[i][j] = new Empty(i, j, board);

                            for (int c = 0; c < gridSize; ++c) {
                                for (int d = 0; d < gridSize; ++d) {
                                    if (board[c][d]->canMove(a, b) && !inCheckTest(c, d, a, b, otherColour)) {
                                        safeMove = false;
                                    }
                                }
                            }
                        
                            delete board[i][j]; // undo the dummy move
                            board[i][j] = board[a][b];
                            board[i][j]->setRow(i);
                            board[i][j]->setCol(j);
                            board[a][b] = temp;

                            if (safeMove) {
                                level4moves.push_back(convertTile(i, j) + convertTile(a, b));
                            }
                        }
                    }
                }
            }
        }
    }

    return level4moves;
}

Game::Game() {

    board.resize(gridSize, vector<Piece*>(gridSize));
    td = new TextDisplay();
    gd = new GraphicsDisplay();
    defaultSetup();
    boardAlreadyInitalized = true;

}

Game::~Game(){

    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            delete board[row][col];
        }
    }

    delete td;
    td = nullptr;

    delete gd;
    gd = nullptr;
}



void Game::makePlayer(char colour, bool isComputer, int level) {
    if (colour == 'w') {
        if (isComputer) {
            delete whiteplayer;
            whiteplayer = new Computer(colour, 0, isComputer, level, board);
            
        }
        else {
            delete whiteplayer;
            whiteplayer = new Player(colour, 0, isComputer);
        }
    }
    else {
        if (isComputer) {
            delete blackplayer;
            blackplayer = new Computer(colour, 0, isComputer, level, board);
        }
        else {
            delete blackplayer;
            blackplayer = new Player(colour, 0, isComputer);
        }
    }
}

Player& Game::finalscore(char colour) {
    if (colour == 'w') return *wtemp;
    else return *btemp;
}

Player& Game::getPlayer(char colour) {
    if (colour == 'w') {
        return *whiteplayer;
    }
    else {
        return *blackplayer;
    }
}

void Game::cpuMove() {
    // move white as cpu
    if (whiteGoesNext) {
        cpuIsMoving = true;
        whiteplayer->bestMove(*this);
        cpuIsMoving = false;
    }
    // move black as cpu
    else {
        cpuIsMoving = true;
        blackplayer->bestMove(*this);
        cpuIsMoving = false;
    }
}


bool Game::move(string startTile, string endTile){
    int startRow = convertRow(startTile);
    int startCol = convertCol(startTile);
    int endRow = convertRow(endTile);
    int endCol = convertCol(endTile);

    Piece *p = board[startRow][startCol];
            
    

    // If they try to move an empty piece
    if (p->getColour() == 'e'){
        if (!cpuIsMoving) cout << "No piece was selected." << endl;
        return false;
    }

    // Check whos turn it is, make sure the player is moving their own piece
    if (p->getColour() != 'w' && whiteGoesNext == true){
        if (!cpuIsMoving) cout << "It is whites turn!" << endl;
        return false;
    } 
    if (p->getColour() != 'b' && whiteGoesNext == false){
        if (!cpuIsMoving) cout << "It is blacks turn!" << endl;
        return false;
    }

    // Using the canMove function of the 
    if (!(p->canMove(endRow, endCol))){
        if (!cpuIsMoving) cout << "Not a legal move." << endl;
        return false;
    } 

    

    // At this point, the move is a "legal" move, but the move could put the player's king in check
    // in which case it would be an illegal move. So we'll make a dummy move to test
    bool moveLeadsToCheck = inCheckTest(startRow, startCol, endRow, endCol, p->getColour());

    if (moveLeadsToCheck){
        if (!cpuIsMoving) cout << "Invalid move. Your king would be in check!" << endl;
        return false;
    }

    // SPECIAL CASE: Castling (at this point, the function has already determined that the king on endTile is legal and not in check)
    if (defaultBoard){
        bool moveRook = false;
        int rookStartRow, rookStartCol, rookEndRow, rookEndCol;
        // Black King
        if (p->getType() == 'k' && p->getColour() == 'b' && startTile == "e8" && endTile == "g8"){  

            // Test move king to f8 to see if its in check
            bool inBetweenTileInCheck  = inCheckTest(0,4,0,5, p->getColour());

            // If start or middle tile in check, not allowed
            if (inCheck('b') || inBetweenTileInCheck){
                if (!cpuIsMoving) cout << "The king must not be in check on either its starting position, its final position, or the position in between" << endl;
                return false;
            }

            // Moving the rook (canMove() should've checked that a rook is there)
            rookStartRow = 0; rookStartCol = 7, rookEndRow = 0, rookEndCol = 5;
            moveRook = true;

        }
        else if (p->getType() == 'k' && p->getColour() == 'b' && startTile == "e8" && endTile == "c8"){  

            // Test move king to d8 to see if its in check
            bool inBetweenTileInCheck  = inCheckTest(0,4,0,3, p->getColour());

            // If start or middle tile in check, not allowed
            if (inCheck('b') || inBetweenTileInCheck){
                if (!cpuIsMoving) cout << "The king must not be in check on either its starting position, its final position, or the position in between" << endl;
                return false;
            }

            // Moving the rook (canMove() should've checked that a rook is there)
            rookStartRow = 0; rookStartCol = 0, rookEndRow = 0, rookEndCol = 3;
            moveRook = true;

        }
        // White King
        else if (p->getType() == 'k' && p->getColour() == 'w' && startTile == "e1" && endTile == "c1"){  

            // Test move king to f8 to see if its in check
            bool inBetweenTileInCheck  = inCheckTest(7,4,7,3, p->getColour());

            // If start or middle tile in check, not allowed
            if (inCheck('b') || inBetweenTileInCheck){
                if (!cpuIsMoving) cout << "The king must not be in check on either its starting position, its final position, or the position in between" << endl;
                return false;
            }

            // Moving the rook (canMove() should've checked that a rook is there)
            rookStartRow = 7; rookStartCol = 0, rookEndRow = 7, rookEndCol = 3;
            moveRook = true;

        }
        else if (p->getType() == 'k' && p->getColour() == 'w' && startTile == "e1" && endTile == "g1"){  

            // Test move king to f8 to see if its in check
            bool inBetweenTileInCheck  = inCheckTest(7,4,7,5, p->getColour());

            // If start or middle tile in check, not allowed
            if (inCheck('b') || inBetweenTileInCheck){
                if (!cpuIsMoving) cout << "The king must not be in check on either its starting position, its final position, or the position in between" << endl;
                return false;
            }

            // Moving the rook (canMove() should've checked that a rook is there)
            rookStartRow = 7; rookStartCol = 7, rookEndRow = 7, rookEndCol = 5;
            moveRook = true;

        }

        if (moveRook){ // Moves the rook
            delete board[rookEndRow][rookEndCol];
            board[rookEndRow][rookEndCol] = board[rookStartRow][rookStartCol];
            board[rookStartRow][rookStartCol] = new Empty(rookStartRow, rookStartCol, board);

            board[rookEndRow][rookEndCol]->setRow(rookEndRow);
            board[rookEndRow][rookEndCol]->setCol(rookEndCol);

            td->tdNotify(board[rookStartRow][rookStartCol]->getColour(), board[rookStartRow][rookStartCol]->getType(), rookStartRow, rookStartCol);
            td->tdNotify(board[rookEndRow][rookEndCol]->getColour(), board[rookEndRow][rookEndCol]->getType(), rookEndRow, rookEndCol);
            gd->gdNotify(board[rookStartRow][rookStartCol]->getColour(), board[rookStartRow][rookStartCol]->getType(), rookStartRow, rookStartCol);
            gd->gdNotify(board[rookEndRow][rookEndCol]->getColour(), board[rookEndRow][rookEndCol]->getType(), rookEndRow, rookEndCol);
        }

    } else if (!defaultBoard){ // Castling Should be disallowed behavior in non default setup
        if (p->getType() == 'k' && p->getColour() == 'b' && startTile == "e8" && (endTile == "g8" || endTile == "c8")){
            if (!cpuIsMoving) cout << "No castling since board was not default setup." << endl;
            return false;
        }
        else if (p->getType() == 'k' && p->getColour() == 'w' && startTile == "e1" && (endTile == "g1" || endTile == "c1")){
            if (!cpuIsMoving) cout << "No castling since board was not default setup." << endl;
            return false;
        }
         
    }

    // SPECIAL CASE: EN PASSANT PART 1
    // Note: at this point, what defines an en-passant attempt is ... 1. It's a pawn 2. It's moving diagonally to an empty tile
    // This code section shall reject all en-passant attempts that are illegal
    if (defaultBoard){

        if (p->getType() == 'p' && p->getColour() == 'w' && board[endRow][endCol]->getType() == 'e'  //White en passanting black
                    && abs(startCol - endCol) == 1 && enPassantColumn == endCol && enPassantAvailable){                     
            delete board[3][enPassantColumn];
            board[3][enPassantColumn] = new Empty(3, enPassantColumn, board); // Remove the pawn that got en passanted
            td->tdNotify(board[3][enPassantColumn]->getColour(), board[3][enPassantColumn]->getType(), 3, enPassantColumn);
            gd->gdNotify(board[3][enPassantColumn]->getColour(), board[3][enPassantColumn]->getType(), 3, enPassantColumn);
        }

        else if (p->getType() == 'p' && p->getColour() == 'b' && board[endRow][endCol]->getType() == 'e'  //Black en passanting white
                    && abs(startCol - endCol) == 1 && enPassantColumn == endCol && enPassantAvailable){      
            delete board[4][enPassantColumn];
            board[4][enPassantColumn] = new Empty(4, enPassantColumn, board);  // Remove the pawn that got en passanted
            td->tdNotify(board[4][enPassantColumn]->getColour(), board[4][enPassantColumn]->getType(), 4, enPassantColumn);
            gd->gdNotify(board[4][enPassantColumn]->getColour(), board[4][enPassantColumn]->getType(), 4, enPassantColumn);
        }
        else if (p->getType() == 'p' && board[endRow][endCol]->getType() == 'e' && abs(startCol - endCol) == 1){
            if (!cpuIsMoving) cout << "Invalid en passant attempt." << endl;
            return false;
        }

    }
    else {
        if (p->getType() == 'p' && board[endRow][endCol]->getType() == 'e' && abs(startCol - endCol) == 1){
            if (!cpuIsMoving) cout << "No en passant since board was not default setup." << endl;
            return false;
        }

    }

    // SPECIAL CASE: Pawn Promotion
    // At this point, we are sure the pawn move is legal since it has passed all the possible rejections.
    if (p->getType() == 'p' && (endRow == 0 || endRow == gridSize - 1)){
        if (pawnPromotePiece == "x" && !cpuIsMoving){
            if (!cpuIsMoving) cout << "You must choose a piece to promote your pawn to." << endl;
            return false;
        }
        else{
            char pawnColor = p->getColour();
            if (cpuIsMoving || pawnPromotePiece == "q" || pawnPromotePiece == "Q" ){
                delete board[startRow][startCol];
                board[startRow][startCol] = new Queen(pawnColor, startRow, startCol, board);
                p = board[startRow][startCol];
            }
            if (pawnPromotePiece == "b" || pawnPromotePiece == "B" ){
                delete board[startRow][startCol];
                board[startRow][startCol] = new Bishop(pawnColor, startRow, startCol, board);
                p = board[startRow][startCol];
            }
            else if (pawnPromotePiece == "r" || pawnPromotePiece == "R" ){
                delete board[startRow][startCol];
                board[startRow][startCol] = new Rook(pawnColor, startRow, startCol, board);
                p = board[startRow][startCol];
            }
            else if (pawnPromotePiece == "n" || pawnPromotePiece == "N" ){
                delete board[startRow][startCol];
                board[startRow][startCol] = new Knight(pawnColor, startRow, startCol, board);
                p = board[startRow][startCol];
            }
            
        }
    }

    // MAKING THE MOVE
    delete board[endRow][endCol];
    board[endRow][endCol] = p;
    board[startRow][startCol] = new Empty(startRow, startCol, board);

    p->setRow(endRow);
    p->setCol(endCol);
    p->moved();

    td->tdNotify(board[startRow][startCol]->getColour(), board[startRow][startCol]->getType(), startRow, startCol);
    td->tdNotify(board[endRow][endCol]->getColour(), board[endRow][endCol]->getType(), endRow, endCol);
    gd->gdNotify(board[startRow][startCol]->getColour(), board[startRow][startCol]->getType(), startRow, startCol);
    gd->gdNotify(board[endRow][endCol]->getColour(), board[endRow][endCol]->getType(), endRow, endCol);

    whiteGoesNext = !whiteGoesNext;

    cout << *td << endl;
    
    // SPECIAL CASE: EN PASSANT PART 2 
    // If a pawn made an initial move of 2, enPassantAvailable is set to true only for the next move (aka en passant must be done immediately)
    if (defaultBoard && p->getType() == 'p' && abs(startRow - endRow) == 2){
        enPassantAvailable = true;
        enPassantColumn = endCol;
    } else {
        enPassantAvailable = false;
    }


    return true;
    
}

void Game::addPiece(string tile, char pieceLetter){
    int row = convertRow(tile);
    int col = convertCol(tile);
    defaultBoard = false;

    delete board[row][col];

    char colour = 'b';
    if (std::isupper(pieceLetter)) colour = 'w';
    if (pieceLetter == 'p' || pieceLetter == 'P') board[row][col] = new Pawn(colour, row, col, board);
    else if (pieceLetter == 'r' || pieceLetter == 'R') board[row][col] = new Rook( colour, row, col, board);
    else if (pieceLetter == 'n' || pieceLetter == 'N') board[row][col] = new Knight(colour, row, col, board);
    else if (pieceLetter == 'b' || pieceLetter == 'B') board[row][col] = new Bishop( colour, row, col, board);
    else if (pieceLetter == 'q' || pieceLetter == 'Q') board[row][col] = new Queen( colour, row, col, board);
    else if (pieceLetter == 'k' || pieceLetter == 'K') board[row][col] = new King( colour, row, col, board);

    td->tdNotify(board[row][col]->getColour(), board[row][col]->getType(), row, col);
    gd->gdNotify(board[row][col]->getColour(), board[row][col]->getType(), row, col);


}

void Game::removePiece(string tile){
    int row = convertRow(tile);
    int col = convertCol(tile);
    defaultBoard = false;

    delete board[row][col];
    board[row][col] = new Empty(row, col, board);

    td->tdNotify('e', 'e', row, col);
    gd->gdNotify('e', 'e', row, col);

}

void Game::clearBoard(){

    // Clear Board
    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            delete board[row][col];
            board[row][col] = new Empty(row, col, board);
        }
    }

    // Update TextDisplay
    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            td->tdNotify('e', 'e', row, col);
            gd->gdNotify('e', 'e', row, col);
        }
    }


}

void Game::defaultSetup(){
    defaultBoard = true;

    // delete all dynamically allocated memory only if the board is not being set up for the first time

    if (boardAlreadyInitalized){ // The board is either entirely dynamically allocated, or being set up for the first time
        for (int row = 0; row < gridSize; row++){
            for (int col = 0; col < gridSize; col++){
                delete board[row][col];
                board[row][col] = nullptr;
            }
        }
    }

    // Black
    board[0][0] = new Rook('b',0, 0, board);
    board[0][1] = new Knight('b',0, 1, board);
    board[0][2] = new Bishop('b',0, 2,board);
    board[0][3] = new Queen('b',0, 3,board);
    board[0][4] = new King('b',0, 4, board);
    board[0][5] = new Bishop('b',0, 5, board);
    board[0][6] = new Knight('b',0, 6, board);
    board[0][7] = new Rook('b',0, 7, board);
    for (int i  = 0; i < gridSize; i++) board[1][i] = new Pawn('b',1, i, board);

    // Empty 
    for (int i  = 0; i < gridSize; i++) board[2][i] = new Empty(2, i, board);
    for (int i  = 0; i < gridSize; i++) board[3][i] = new Empty(3, i, board);
    for (int i  = 0; i < gridSize; i++) board[4][i] = new Empty(4, i, board);
    for (int i  = 0; i < gridSize; i++) board[5][i] = new Empty(5, i, board);

    // White
    for (int i  = 0; i < gridSize; i++) board[6][i] = new Pawn('w',6, i, board);
    board[7][0] = new Rook('w',7, 0, board);
    board[7][1] = new Knight('w',7, 1, board);
    board[7][2] = new Bishop('w',7, 2, board);
    board[7][3] = new Queen('w',7, 3, board);
    board[7][4] = new King('w',7, 4, board);
    board[7][5] = new Bishop('w',7, 5, board);
    board[7][6] = new Knight('w',7, 6, board);
    board[7][7] = new Rook('w',7, 7, board);

    // Update TextDisplay
    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            td->tdNotify(board[row][col]->getColour(), board[row][col]->getType(), row, col);
            gd->gdNotify(board[row][col]->getColour(), board[row][col]->getType(), row, col);
        }
    }

}

// This function will check the following:
// no pawns first and last row, exactly one king, checkmate, stalemate
bool Game::isGameOver(){

    // CHECKING FOR: No pawns first and last row
    for (int j  = 0; j < gridSize; j++){
        if (board[0][j]->getType() == 'p'){
            cout << "No pawns allowed on first and last row." << endl;
            return true;
        } 
    }
    for (int j  = 0; j < gridSize; j++){
        if (board[7][j]->getType() == 'p'){
            cout << "No pawns allowed on first and last row." << endl;
            return true;
        } 
    }

    // CHECKING FOR: Exactly one king
    int whiteKingCounter = 0;
    int blackKingCounter = 0;
    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            if (board[row][col]->getType() == 'k' && board[row][col]->getColour() == 'w') whiteKingCounter++;
            if (board[row][col]->getType() == 'k' && board[row][col]->getColour() == 'b') blackKingCounter++;
        }
    }
    if (whiteKingCounter != 1 || blackKingCounter != 1){
        cout << "There must be exactly one king per side." << endl;
        return true;
    }

    //CHECKING FOR: Checkmate and Stalemate

    bool canWhiteMove = generateLegalMoves('w');
    bool isWhiteCheck = inCheck('w');
    bool canBlackMove = generateLegalMoves('b');
    bool isBlackCheck = inCheck('b');

    if (canWhiteMove == false && isWhiteCheck == true){
        cout << "Checkmate." << endl;
        cout << "Black wins!" << endl;
        blackplayer->changeScore(1);
        btemp->changeScore(blackplayer->getScore());
        return true;
    }
    if (canWhiteMove == false && isWhiteCheck == false){
        cout << "Stalemate." << endl;
        blackplayer->changeScore(0.5);
        btemp->changeScore(blackplayer->getScore());
        whiteplayer->changeScore(0.5);
        wtemp->changeScore(whiteplayer->getScore());
        return true;
    } 
    if (canBlackMove == false && isBlackCheck == true){
        cout << "Checkmate." << endl;
        cout << "White wins!" << endl;
        whiteplayer->changeScore(1);
        wtemp->changeScore(whiteplayer->getScore());            
        return true;
    }
    if (canBlackMove == false && isBlackCheck == false){
        cout << "Stalemate." << endl;
        blackplayer->changeScore(0.5);
        btemp->changeScore(blackplayer->getScore());
        whiteplayer->changeScore(0.5);
        wtemp->changeScore(whiteplayer->getScore());
        return true;
    } 

    // Additional Stalemate Cases:
    // If both players are left with a bare king, the game is immediately drawn. 
     // Similarly, if one player has only a king and either a bishop or a knight while the opponent has a bare king, the game is immediately drawn.
    int whitePieceCounter = 0;
    int blackPieceCounter = 0;
    bool whiteHasKnightOrBishop = false;
    bool blackHasKnightOrBishop = false;

    // Function assumes there will always be a king on the board
    for (int row = 0; row < gridSize; row++){
        for (int col = 0; col < gridSize; col++){
            if (board[row][col]->getColour() == 'b'){
                blackPieceCounter++;
                if (board[row][col]->getType() == 'n' || board[row][col]->getType() == 'b'){
                    blackHasKnightOrBishop = true;
                }
            }
            if (board[row][col]->getColour() == 'w'){
                whitePieceCounter++;
                if (board[row][col]->getType() == 'n' || board[row][col]->getType() == 'b'){
                    whiteHasKnightOrBishop = true;
                }
            }
        }
    }

    if (whitePieceCounter == 1 && blackPieceCounter == 1){
        cout << "Stalemate." << endl;
        blackplayer->changeScore(0.5);
        btemp->changeScore(blackplayer->getScore());
        whiteplayer->changeScore(0.5);
        wtemp->changeScore(whiteplayer->getScore());
        return true;
    }
    if (whitePieceCounter == 1 && blackPieceCounter == 2 && blackHasKnightOrBishop){
        cout << "Stalemate." << endl;
        blackplayer->changeScore(0.5);
        btemp->changeScore(blackplayer->getScore());
        whiteplayer->changeScore(0.5);
        wtemp->changeScore(whiteplayer->getScore());
        return true;
    }
    if (blackPieceCounter == 1 && whitePieceCounter == 2 && whiteHasKnightOrBishop){
        cout << "Stalemate." << endl;
        blackplayer->changeScore(0.5);
        btemp->changeScore(blackplayer->getScore());
        whiteplayer->changeScore(0.5);
        wtemp->changeScore(whiteplayer->getScore());
        return true;
    }

    // Game isn't over but in check
    if (isWhiteCheck) cout << "White is in check." << endl;
    if (isBlackCheck) cout << "Black is in check." << endl;

    return false;
}

void Game::gameStart(bool whiteGoesNext){
    this->whiteGoesNext = whiteGoesNext;
}

void Game::pawnPromoteAttempt(string pieceLetter){
    pawnPromotePiece = pieceLetter;
}


bool Game::getTurn() {
    return whiteGoesNext;
}

ostream &operator<<(ostream &out, const Game &g) {
        return out << *g.td;
}
