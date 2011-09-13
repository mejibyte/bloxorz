#include "Cell.h"

Cell::Cell() {
}

Cell::Cell(int row, int col, bool empty, bool weak, bool winningHole) {
    
    
}

int Cell::getRow() const {
    //TODO: Implement this method    
    return 1;
}

int Cell::getColumn() const {
    //TODO: Implement this method    
    return 1;
}


bool Cell::isHollow() const{
    //TODO: Implement this method    
    return (rand() % 3 == 0);
}

bool Cell::isWeak() const {
    //TODO: Implement this method    
    return (rand() % 3 == 0);    
}

bool Cell::isWinningHole() const {
    //TODO: Implement this method    
    return (rand() % 4 == 0);    
}
