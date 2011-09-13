#include "Board.h"

Board::Board(){
    // Empty constructor, does nothing.
}

Board::Board(string filename){
    Board();
    
    ifstream in(filename.c_str());
    assert(in >> rows >> cols);
    assert(rows > 0 and cols > 0);
    cells.clear();
    tile = Tile();    
    for (int i = 0; i < rows; ++i){
        string line;
        in >> line;
        cells.push_back(vector<Cell>(0));
        assert(line.size() == cols);
        for (int j = 0; j < cols; ++j){
            char c = line[j];
            if (c == 'S'){ // solid
                cells.back().push_back(Cell(i, j, false, false, false));
            }else if(c == 'H'){
                cells.back().push_back(Cell(i, j, true, false, false));
            }else if(c == 'K'){
                cells.back().push_back(Cell(i, j, false, true, false));                
            }else if(c == 'W'){
                cells.back().push_back(Cell(i, j, false, false, true));                
            }else if(c == 'T'){
                cells.back().push_back(Cell(i, j, false, false, false));
                tile.addCell(cells.back().back());
            }else{
                assert(false);
            }
        }
    }
    assert(cells.size() == rows);
    assert(cells[0].size() == cols);
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