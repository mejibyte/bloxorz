#pragma once

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
};