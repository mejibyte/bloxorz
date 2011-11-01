#pragma once

#include "Board.h"

class AbstractView {
public:
    static const int WIDTH = 700;
    static const int HEIGHT = 700;
    virtual void setBoard(Board board) = 0;
    virtual void refresh() = 0;
    virtual void reshape(int newWidth, int newHeight) = 0;
    virtual void setMessage(const char * message) = 0;
    virtual void clearMessage() = 0;   
    virtual void cameraUp();
	virtual void cameraDown();
	virtual void cameraLeft();
	virtual void cameraRight();
    
protected:
    Board board;
};