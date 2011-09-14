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
            }else if(c == 'H'){ // hollow
                cells.back().push_back(Cell(i, j, true, false, false));
            }else if(c == 'K'){ // weak
                cells.back().push_back(Cell(i, j, false, true, false));                
            }else if(c == 'W'){ // winning hole
                cells.back().push_back(Cell(i, j, false, false, true));                
            }else if(c == 'T'){ // tile
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
    if (outside(row, col)){
     throw "Invalid arguments: both row and col must be inside the board.";
    } else {
        return cells[row][col];        
    }
}

bool Board::outside(int row, int col) {
    return (row < 0 or row >= getRows() or col < 0 or col >= getCols());
}

// Returns wheter you've won the game or not.
bool Board::isWinningPosition() {
    if (isLosingPosition()) return false;
    if (tile.isLayingDown()) return false;
    const Cell c = tile.getCurrentCells().front();
    return getCellAt(c.getRow(), c.getColumn()).isWinningHole();
}

// Returns wheter you've lost the game or not.
bool Board::isLosingPosition() {
    const vector<Cell> &cells = tile.getCurrentCells();
    for (int k = 0; k < cells.size(); ++k){
        if (outside(cells[k].getRow(), cells[k].getColumn())) return true;
    }
    Cell c = cells.front();
    return (tile.isStandingUp() && getCellAt(c.getRow(), c.getColumn()).isWeak());
}
// Moves the tile in the given direction, even if it results in an invalid board (like the tile outside the solid cells or standing straight on a weak cell) 
void Board::moveTile(Direction direction) {
                    //Up, Right, Down, Left    
    int deltaRow[] = { -1, +0, +1, +0 };
    int deltaCol[] = { +0, +1, +0, -1 };
    
    if (tile.isStandingUp()){ // make it lay down in the given direction
        int row = tile.getCurrentCells().front().getRow(), col = tile.getCurrentCells().front().getColumn();
        tile.clearCells();
        tile.addCell(Cell(row + deltaRow[direction], col + deltaCol[direction]));
        tile.addCell(Cell(row + 2 * deltaRow[direction], col + 2 * deltaCol[direction]));        
        
    } else { // laying down
        vector<Cell> cells = tile.getCurrentCells();
        int row1 = cells.front().getRow(),    row2 = cells.back().getRow();
        int col1 = cells.front().getColumn(), col2 = cells.back().getColumn();
        assert(row1 == row2 or col1 == col2);

        tile.clearCells();
        if (row1 == row2) { // horizontal
            if (direction == Board::Up or direction == Board::Down) {
                // just move the two cells in the given direction
                tile.addCell(Cell(row1 + deltaRow[direction], col1 + deltaCol[direction]));
                tile.addCell(Cell(row2 + deltaRow[direction], col2 + deltaCol[direction]));                
            } else if (direction == Board::Left) {
                tile.addCell(Cell(row1 + deltaRow[direction], min(col1, col2) + deltaCol[direction]));
            } else { // Direction == Right
                tile.addCell(Cell(row1 + deltaRow[direction], max(col1, col2) + deltaCol[direction]));                
            }
        } else { // vertical, col1 == col2
            if (direction == Board::Left or direction == Board::Right){
                // just move the two cells in the given direction
                tile.addCell(Cell(row1 + deltaRow[direction], col1 + deltaCol[direction]));
                tile.addCell(Cell(row2 + deltaRow[direction], col2 + deltaCol[direction]));                                
            } else if (direction == Board::Up) {
                tile.addCell(Cell(min(row1, row2) + deltaRow[direction], col1 + deltaCol[direction]));
            } else { // direction == Down
                tile.addCell(Cell(max(row1, row2) + deltaRow[direction], col1 + deltaCol[direction]));                
            }
        }
    }
    assert(tile.getCurrentCells().size() == 1 or tile.getCurrentCells().size() == 2);
}