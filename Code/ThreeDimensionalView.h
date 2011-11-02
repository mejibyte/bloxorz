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
#include <cmath>
#include <cassert>

#include <stdlib.h>
#include <algorithm>


#include "AbstractView.h"
#include "Board.h"
#include "RgbImage.h"

class ThreeDimensionalView : public AbstractView {
public:
    ThreeDimensionalView();
    ThreeDimensionalView(Board board);    
    void setBoard(Board board);
    void refresh();
    void reshape(int newWidth, int newHeight);
    void setMessage(const char * message);
    void cameraUp();
    void cameraDown();
	void cameraLeft();
	void cameraRight();
    void resetCamera();
    void clearMessage();
    void animateStraightFall();    
    void animateRotatingFall();
    
private:
    //int cellWidth();
    //int cellHeight();    
    void drawCubeAt(int row, int col,        float color[]);
    void drawTileAt(int row, int col, bool standingUp, long double deltaZ = 0.0);
    void drawTileWithRotation(int row, int col, bool standingUp, long double deltaZ, double angleOfRotation, string axisOfRotation);     
    void drawBoard();
    void drawTileFalling(int row, int col, bool standingUp);
    void setPerspective();
    void solidCubeWithTexture(GLfloat size);
    GLuint loadTexture( const char * filename, bool wrap );
    void loadTextureFromFile(char *filename);
    string message;
};