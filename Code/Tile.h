#pragma once

#include <vector>

#include "Cell.h"

using namespace std;

class Tile {
public:   
    Tile();
    bool isStandingUp();
    bool isLayingDown();
    vector<Cell> getCurrentCells();
    void addCell(Cell someCellWhereTheTileIs);
private:
    vector<Cell> cells;
};