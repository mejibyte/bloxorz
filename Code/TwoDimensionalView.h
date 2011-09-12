#pragma once

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "AbstractView.h"
#include "Board.h"

class TwoDimensionalView : public AbstractView {
public:
    TwoDimensionalView();
    TwoDimensionalView(Board board);    
    void setBoard(Board board);
    void refresh();
private:
    int cellWidth();
    int cellHeight();    
    void drawRectangleAt(int row, int col,        double r, double g, double b);
};