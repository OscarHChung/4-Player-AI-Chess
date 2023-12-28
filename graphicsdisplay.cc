#include <iostream>
#include "graphicsdisplay.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(){

    xw = new Xwindow();

    bool alternator = true;

    xw->fillRectangle(23, 23, 604, 604, Xwindow::Black);
    // Fill Xwindow with green/white squares
    for (int i = 0; i < gridSize ; i++){
        for (int j  = 0; j < gridSize; j++){
            if (alternator) xw->fillRectangle(i*75+25, j*75+25, 75, 75,  Xwindow::Chess_White);
            else xw->fillRectangle(i*75+25, j*75+25, 75, 75, Xwindow::Chess_Green);
            if (j!=7) alternator = !alternator;
        }
    }
    xw->drawString(60,15,"a");
    xw->drawString(135,15,"b");
    xw->drawString(210,15,"c");
    xw->drawString(285,15,"d");
    xw->drawString(360,15,"e");
    xw->drawString(435,15,"f");
    xw->drawString(510,15,"g");
    xw->drawString(585,15,"h");

    xw->drawString(60,640,"a");
    xw->drawString(135,640,"b");
    xw->drawString(210,640,"c");
    xw->drawString(285,640,"d");
    xw->drawString(360,640,"e");
    xw->drawString(435,640,"f");
    xw->drawString(510,640,"g");
    xw->drawString(585,640,"h");

    xw->drawString(10,65,"8");
    xw->drawString(10,140,"7");
    xw->drawString(10,205,"6");
    xw->drawString(10,280,"5");
    xw->drawString(10,355,"4");
    xw->drawString(10,430,"3");
    xw->drawString(10,505,"2");
    xw->drawString(10,580,"1");

    xw->drawString(635,65,"8");
    xw->drawString(635,140,"7");
    xw->drawString(635,205,"6");
    xw->drawString(635,280,"5");
    xw->drawString(635,355,"4");
    xw->drawString(635,430,"3");
    xw->drawString(635,505,"2");
    xw->drawString(635,580,"1");

    
}

void GraphicsDisplay::gdNotify(char colour, char pieceLetter, int row, int col){
    int gdRow = 25 + row * 75;
    int gdCol = 25 + col * 75;
    if (colour == 'b'){
        if (pieceLetter == 'r'){
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::Black);
            xw->drawWhiteString(26+gdCol,40+gdRow,"Rook");
        }
        else if (pieceLetter == 'b'){
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::Black);
            xw->drawWhiteString(21+gdCol,40+gdRow,"Bishop");
        }
        else if (pieceLetter == 'n'){
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::Black);
            xw->drawWhiteString(20+gdCol,40+gdRow,"Knight");
        }
        else if (pieceLetter == 'q'){
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::Black);
            xw->drawWhiteString(23+gdCol,40+gdRow,"Queen");
        }
        else if (pieceLetter == 'k'){
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::Black);
            xw->drawWhiteString(26+gdCol,40+gdRow,"King");
        }
        else if (pieceLetter == 'p'){
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::Black);
            xw->drawWhiteString(26+gdCol,40+gdRow,"Pawn");
        }
    }
    else if (colour == 'w'){
        if (pieceLetter == 'r'){
            xw->fillRectangle(14+gdCol, 19+gdRow, 47, 37, Xwindow::Black);
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::White);
            xw->drawString(26+gdCol,40+gdRow,"Rook");
        }
        else if (pieceLetter == 'b'){
            xw->fillRectangle(14+gdCol, 19+gdRow, 47, 37, Xwindow::Black);
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::White);
            xw->drawString(21+gdCol,40+gdRow,"Bishop");
        }
        else if (pieceLetter == 'n'){
            xw->fillRectangle(14+gdCol, 19+gdRow, 47, 37, Xwindow::Black);
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::White);
            xw->drawString(20+gdCol,40+gdRow,"Knight");
        }
        else if (pieceLetter == 'q'){
            xw->fillRectangle(14+gdCol, 19+gdRow, 47, 37, Xwindow::Black);
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::White);
            xw->drawString(23+gdCol,40+gdRow,"Queen");
        }
        else if (pieceLetter == 'k'){
            xw->fillRectangle(14+gdCol, 19+gdRow, 47, 37, Xwindow::Black);
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::White);
            xw->drawString(26+gdCol,40+gdRow,"King");
        }
        else if (pieceLetter == 'p'){
            xw->fillRectangle(14+gdCol, 19+gdRow, 47, 37, Xwindow::Black);
            xw->fillRectangle(15+gdCol, 20+gdRow, 45, 35, Xwindow::White);
            xw->drawString(26+gdCol,40+gdRow,"Pawn");
        }
    }
    else if (colour == 'e'){
        if (((row + col) %  2) == 0)  xw->fillRectangle(col*75+25, row*75+25, 75, 75,  Xwindow::Chess_White);
        else  xw->fillRectangle(col*75+25, row*75+25, 75, 75, Xwindow::Chess_Green);
    }
    
    
}

GraphicsDisplay::~GraphicsDisplay() {
    delete xw;
    xw = nullptr;
}
