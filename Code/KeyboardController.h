#pragma once

#ifdef __APPLE__
#include <GLUT/glut.h>
#elif defined _WIN32 || defined _WIN64
#include <GL/glut.h>
#endif 

#include <cstdio>
#include <string>
#include <sstream>
#include <sys/stat.h>

#include "AbstractController.h"
#include "TwoDimensionalView.h"

using namespace std;

class KeyboardController : AbstractController {
public:
    KeyboardController();
    KeyboardController(string boardsDir);
    
    void cleanUp();
    void refreshView();
    void normalKeyPressed(unsigned char key);
    void specialKeyPressed(int key);  
    void reshapeView(int newWidth, int newHeight);
private:
    bool loadBoard(int boardNumber);
    bool isThereNextLevel();
};