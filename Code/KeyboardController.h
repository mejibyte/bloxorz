#pragma once

#ifdef __APPLE__
#include <GLUT/glut.h>
#elif defined _WIN32 || defined _WIN64
#include <GL/glut.h>
#endif 

#include <cstdio>

#include "AbstractController.h"
#include "TwoDimensionalView.h"

class KeyboardController : AbstractController {
public:
    void prepare();
    void cleanUp();
    void refreshView();
    void normalKeyPressed(unsigned char key);
    void specialKeyPressed(int key);  
    void reshapeView(int newWidth, int newHeight);    
};