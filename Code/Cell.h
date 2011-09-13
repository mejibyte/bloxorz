#pragma once

#include <cstdlib>

class Cell {
public:
    Cell(int row, int col, bool empty, bool weak, bool winningHole);
    Cell();
    // Returns the row of this cell.    
    int getRow() const;
    // Returns the column of this cell.    
    int getColumn() const;
    // Returns true if the tile can't stand up here (no cell).
    bool isHollow() const;
    // Returns wether the cell is weak or not.
    bool isWeak() const;
    // Returns wether this cell is the winning hole or not.
    bool isWinningHole() const;
};