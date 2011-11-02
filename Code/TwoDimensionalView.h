#pragma once

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <string>

#include "AbstractView.h"
#include "Board.h"

class TwoDimensionalView : public AbstractView {
public:
    TwoDimensionalView();
    TwoDimensionalView(Board board);    
    void setBoard(Board board);
    void refresh();
    void reshape(int newWidth, int newHeight);
    void setMessage(const char * message);
    void clearMessage();    
    void cameraUp();
    void cameraDown();
	void cameraLeft();
	void cameraRight();
    void resetCamera();
    void animateStraightFall();
    void animateRotatingFall();
    
private:
    int cellWidth();
    int cellHeight();    
    void drawRectangleAt(int row, int col,        double r, double g, double b);
    string message;
};