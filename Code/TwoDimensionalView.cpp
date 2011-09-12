#include "TwoDimensionalView.h"


TwoDimensionalView::TwoDimensionalView(){
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);	// Left, Right, Bottom, Top corners    
}

TwoDimensionalView::TwoDimensionalView(Board board){
    TwoDimensionalView();
    setBoard(board);
}

void TwoDimensionalView::setBoard(Board someBoard) {
    board = someBoard;
}

void TwoDimensionalView::refresh() {
    puts("[VIEW] called refresh()");
    glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.
    
    int rows = board.getRows();
    int cols = board.getCols();
    
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            Cell c = board.getCellAt(i, j);
            double r = 0.5, g = 0.5, b = 0.5;
            if (c.isHollow()){
                r = 0, g = 0, b = 0;
            }else if (c.isWeak()){
                r = 1, g = 165./255., b = 0;
            }else if (c.isWinningHole()){
                r = 1, g = 0, b = 0;
            }
            drawRectangleAt(i, j,    r, g, b);
        }
    }    
    glFlush();
}

int TwoDimensionalView::cellWidth() {
    return WIDTH / board.getCols();
}

int TwoDimensionalView::cellHeight() {
    return HEIGHT / board.getRows();
}


void TwoDimensionalView::drawRectangleAt(int row, int col,        double r, double g, double b) {
    printf("Drawing rectangle at <%d, %d>\n", row, col);
    int w = cellWidth();
    int h = cellHeight();
    
    int leftX = w * col;
    int rightX = leftX + w;
    
    int topY = h * row;
    int bottomY = topY + h;
    
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex2i(leftX, topY);
    glVertex2i(leftX, bottomY);
    glVertex2i(rightX, bottomY);
    glVertex2i(rightX, topY);
    glEnd();
}