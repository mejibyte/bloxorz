#pragma once

#include <string>

#include "Board.h"
#include "AbstractView.h"

using namespace std;

class AbstractController {
public:    
    // Runs the game and synchronizes calls between the model and the view as necessary.
    virtual void refreshView() = 0;
    virtual void reshapeView(int newWidth, int newHeight) = 0;    
    virtual void normalKeyPressed(unsigned char key) = 0;
    virtual void specialKeyPressed(int key) = 0;    
    virtual void cleanUp() = 0;
protected:
    Board board;
    AbstractView * view;
    string boardsDir; // Path to the folder where the boards are, i.e ~/Games/Bloxorz/boards/
    int currentBoard; // Boards are expected to be named 1.txt, 2.txt, etc. This attribute says what's the board we are currently playing.
};