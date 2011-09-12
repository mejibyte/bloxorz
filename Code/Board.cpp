#include "Board.h"

Board::Board(){
    // Empty constructor, does nothing.
}

Board::Board(string filename){
    // Reads the board from filename
    rows = 4;
    cols = 5;
    // TODO: implement this method
}

int Board::getRows() {
    return rows;
}

int Board::getCols() {
    return cols;
}

Cell Board::getCellAt(int row, int col) {
    // TODO: return an actual cell in the "cells" variable
    return Cell(row, col, false, false, false);
}