#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include "window.h"

using namespace std;

class GraphicsDisplay{
    const int gridSize = 8;
    Xwindow* xw = nullptr;

  public:
    GraphicsDisplay();  // constructor

    void gdNotify(char colour, char pieceLetter, int row, int col); //notify event 
    
    ~GraphicsDisplay(); // destructor

};

#endif
