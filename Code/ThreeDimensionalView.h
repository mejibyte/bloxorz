#pragma once

#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif defined _WIN32 || defined _WIN64
#include <GL/glut.h>
#endif

#include <string>
#include <vector>
   

#include "AbstractView.h"
#include "Board.h"

class ThreeDimensionalView : public AbstractView {
public:
    ThreeDimensionalView();
    ThreeDimensionalView(Board board);    
    void setBoard(Board board);
    void refresh();
    void reshape(int newWidth, int newHeight);
    void setMessage(const char * message);
    void clearMessage();
   void cameraUp();
	void cameraDown();
	void cameraLeft();
	void cameraight();
private:
    //int cellWidth();
    //int cellHeight();    
    void drawCubeAt(int row, int col,        float color[]);
    string message;
};