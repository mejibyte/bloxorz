#include "Cell.h"

Cell::Cell() {
}

Cell::Cell(int row, int col, bool hollow, bool weak, bool winningHole) : row(row), col(col), hollow(hollow), weak(weak), winningHole(winningHole) {
}

int Cell::getRow() const {    
    return row;
}

int Cell::getColumn() const {       
    return col;
}


bool Cell::isHollow() const{
    return hollow;
}

bool Cell::isWeak() const {
    return weak;
}

bool Cell::isWinningHole() const {
    return winningHole;
}
