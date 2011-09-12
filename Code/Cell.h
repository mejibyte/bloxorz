#pragma once

class Cell {
public:    
    // Returns the row of this cell.    
    int getRow();
    // Returns the column of this cell.    
    int getColumn();
    // Returns true if the tile can't stand up here (no cell).
    bool isEmpty();
    // Returns wether the cell is weak or not.
    bool isWeak();
    // Returns wether this cell is the winning hole or not.
    bool isWinningHole();
};