#pragma once

#include <vector>
#include "Cell.h"

using namespace std;

class Tile {
public:    
    bool isStandingUp();
    bool isLayingDown();
    vector<Cell> getCurrentCells();
};