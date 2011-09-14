#pragma once

#include <vector>

#include "Cell.h"

using namespace std;

class Tile {
public:   
    Tile();
    bool isStandingUp() const;
    bool isLayingDown() const;
    vector<Cell> getCurrentCells() const;
    void addCell(Cell someCellWhereTheTileIs);
    void clearCells();
private:
    vector<Cell> cells;
};