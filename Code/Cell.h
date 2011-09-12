#pragma once

#include <cstdlib>

class Cell {
public:
    Cell(int row, int col, bool empty, bool weak, bool winningHole);
    // Returns the row of this cell.    
    int getRow();
    // Returns the column of this cell.    
    int getColumn();
    // Returns true if the tile can't stand up here (no cell).
    bool isHollow();
    // Returns wether the cell is weak or not.
    bool isWeak();
    // Returns wether this cell is the winning hole or not.
    bool isWinningHole();
};