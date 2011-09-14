#pragma once

#include <cstdlib>

class Cell {
public:
    Cell(int row, int col, bool hollow, bool weak, bool winningHole);
    Cell();
    Cell(int row, int col);
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
private:
    int row, col;
    bool hollow, weak, winningHole;
};