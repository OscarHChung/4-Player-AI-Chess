#include <iostream>
#include <string>
#include "game.h"
#include "player.h"

using namespace std;

int main() {

    Game g; // calls game constructor to initialize a game board
    string cmd; // base commands
    string cmd2; // secondary commands for setup
    bool whiteGoesNext = true; 
    bool cpuplay = false;
    bool gameOn = false;


    cout << g << endl;

    while (!cin.eof()) { // while there is input
        cin >> cmd;
        if (cmd == "setup" && !gameOn) {
            while (true){
                cin >> cmd2;
                if (cmd2 == "default") { // default chess board
                    g.defaultSetup();
                    cout << g << endl; // display board
                }
                else if (cmd2 == "+") { // add a piece
                    string tile;
                    char pieceLetter;  
                    cin >> pieceLetter >> tile;
                    if (tile.length() != 2) {
                        cout << "Invalid tile entry, try again!" << endl;
                        continue;
                    }
                    if (tile[0] < 'a' || tile[0] > 'h' || tile[1] < '1' || tile[1] > '8') { // invalid tiles
                        cout << "Invalid entry, try again!" << endl; 
                        continue;
                    }
                    if (pieceLetter == 'k' || pieceLetter == 'b' || pieceLetter == 'n' || pieceLetter == 'q' || pieceLetter == 'p' || pieceLetter == 'r'
                        || pieceLetter == 'K' || pieceLetter == 'B' || pieceLetter == 'N' || pieceLetter == 'Q' || pieceLetter == 'P' || pieceLetter == 'R'){
                        g.addPiece(tile, pieceLetter);
                        cout << g << endl; 
                    }
                         
                }
                else if (cmd2 == "-") { // remove a piece
                    string tile;
                    cin >> tile;
                    if (tile.length() != 2) {
                        cout << "Invalid tile entry, try again!" << endl;
                        continue;
                    }
                    if (tile[0] < 'a' || tile[0] > 'h' || tile[1] < '1' || tile[1] > '8') { // invalid tiles
                        cout << "Invalid tile entry, try again!" << endl;
                        continue;
                    }
                    g.removePiece(tile); // remove piece from board
                    cout << g << endl; // redisplay board
                }
                else if (cmd2 == "=") {
                    string turn;
                    cin >> turn;
                    if (turn == "white") {
                        whiteGoesNext = true;
                    } else if (turn == "black") {
                        whiteGoesNext = false;
                    }
                    else {
                        cout << "Invalid colour, try again!" << endl;
                    }
                }
                else if (cmd2 == "clear") {
                    g.clearBoard(); // clears the board
                    cout << g << endl; // redisplay board
                }
                else if (cmd2 == "done"){
                    if( !g.isGameOver() ){
                        cout << "Valid board, you may begin a game!" << endl;
                        break;
                    }
                    else cout << "Board is invalid, try again!" << endl;
                }
                else {
                    cout << "Invalid setup command, try again!" << endl;
                }
            }
        }
        else if (cmd == "game" && !gameOn) {
            string white_player;
            string black_player;
            bool validP1 = true;
            bool validP2 = true;
            cin >> white_player >> black_player;

            // setup white player
            if (white_player == "human") {
                cpuplay = false;
                g.makePlayer('w', cpuplay, 0);
            }
            // cpu or invalid player input
            else {
                cpuplay = true;
                if (white_player == "computer[1]") {
                    g.makePlayer('w', cpuplay, 1);
                }
                else if (white_player == "computer[2]") {
                    g.makePlayer('w', cpuplay, 2);
                }
                else if (white_player == "computer[3]") {
                    g.makePlayer('w', cpuplay, 3);
                }
                else if (white_player == "computer[4]") {
                    g.makePlayer('w', cpuplay, 4);
                }
                else {
                    cout << "Invalid player, try again!" << endl;
                    validP1 = false;
                }
            }

            if (validP1) {
                // setup black player
                if (black_player == "human") {
                    cpuplay = false;
                    g.makePlayer('b', cpuplay, 0);
                }
                // cpu or invalid player input
                else {
                    cpuplay = true;
                    if (black_player == "computer[1]") {
                        g.makePlayer('b', cpuplay, 1);
                    }
                    else if (black_player == "computer[2]") {
                        g.makePlayer('b', cpuplay, 2);
                    }
                    else if (black_player == "computer[3]") {
                        g.makePlayer('b', cpuplay, 3);
                    }
                    else if (black_player == "computer[4]") {
                        g.makePlayer('b', cpuplay, 4);
                    }
                    else {
                        cout << "Invalid player, try again!" << endl;
                        validP2 = false;
                    }
                }

                if (validP2) {
                    // both players valid
                    gameOn = true;
                    g.gameStart(whiteGoesNext);
                    continue;
                }
            }
        }
        else if (cmd == "move" && gameOn) {
            // if it's a cpu's turn, then cpu moves once
            if (g.getTurn() && g.getPlayer('w').isComputer()) {
                g.cpuMove();
                if (g.isGameOver()){
                    gameOn = false;
                    string input;
                    cout << "Enter anything to continue" << endl;
                    while (cin >> input){
                        if (input != ""){
                            g.clearBoard();
                            cout << "Setup the board to start a new game." << endl;
                            break;
                        }
                    }

                } 
                continue;
            }
            else if (!g.getTurn() && g.getPlayer('b').isComputer()) {
                g.cpuMove();
                if (g.isGameOver()){
                    gameOn = false;
                    string input;
                    cout << "Enter anything to continue" << endl;
                    while (cin >> input){
                        if (input != ""){
                            g.clearBoard();
                            cout << "Setup the board to start a new game." << endl;
                            break;
                        }
                    }

                } 
                continue;
            }

            // otherwise, check for human player input
            string original, end;
            cin >> original >> end;

            string pawnPromote;
            if (cin.peek() != '\n'){
                cin >> pawnPromote;
                if (pawnPromote != "b" && pawnPromote != "B" && pawnPromote != "k" && pawnPromote != "K" &&
                pawnPromote != "r" && pawnPromote != "R" && pawnPromote != "q" && pawnPromote != "Q"){
                    cout << "Not a valid piece!" << endl;
                    continue;
                }
                else g.pawnPromoteAttempt(pawnPromote);
            } else{
                g.pawnPromoteAttempt("x"); // x will indicate nothing entered
            }

            if (original.length() != 2 || end.length() != 2) {
                cout << "Invalid tile entry, try again!" << endl;
                continue;
            }
            else if (original[0] < 'a' || original[0] > 'h' || original[1] < '1' || original[1] > '8') { // invalid tiles
                cout << "Invalid tile, try again!" << endl;
                continue;
            }
            else if (end[0] < 'a' || end[0] > 'h' || end[1] < '1' || end[1] > '8') { // invalid tiles
                cout << "Invalid tile, try again!" << endl; 
                continue;
            }
            g.move(original, end); // move piece
            if (g.isGameOver()){
                    gameOn = false;
                    string input;
                    cout << "Enter anything to continue" << endl;
                    while (cin >> input){
                        if (input != ""){
                            g.clearBoard();
                            cout << "Setup the board to start a new game." << endl;
                            break;
                        }
                    }

                } 
        }
        else if (cmd == "resign" && gameOn) {
            gameOn = false;
            if (g.getTurn()) {
                if (cin.eof()) break;
                cout << "Black wins!" << endl;
                g.clearBoard();
                g.finalscore('b').changeScore(1);
                cout << "Setup the board again!" << endl;
                continue;
            }
            else {
                if (cin.eof()) break;
                cout << "White wins!" << endl;
                g.clearBoard();
                g.finalscore('w').changeScore(1);
                cout << "Setup the board again!" << endl;
                continue;
            }
        }
        else {
            if (gameOn) cout << "There is a game in play right now." << endl;
            else cout << "There is no game in play." << endl;
            cout << "Invalid command, try again!" << endl;
            continue;
        }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << g.finalscore('w').getScore() << endl;
    cout << "Black: " << g.finalscore('b').getScore() << endl;
}

