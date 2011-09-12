#include "Board.h"

Board::Board(){
    // Empty constructor, does nothing.
}

Board::Board(string filename){
    Board();
    
    // TODO: implement this method
    // Reads the board from filename
    rows = 4;
    cols = 5;
    tile = Tile();
}

int Board::getRows() {
    return rows;
}

int Board::getCols() {
    return cols;
}

Tile Board::getTile() {
    return tile;
}

Cell Board::getCellAt(int row, int col) {
    // TODO: return an actual cell in the "cells" variable
    return Cell(row, col, false, false, false);
}