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
    virtual void cameraUp() = 0;
	virtual void cameraDown() = 0;
	virtual void cameraLeft() = 0;
	virtual void cameraRight() = 0;
    virtual void resetCamera() = 0;
    virtual void animateStraightFall() = 0;
protected:
    Board board;
};