#include "Cell.h"

Cell::Cell(int row, int col, bool empty, bool weak, bool winningHole) {
    //TODO: Implement this constructor
}

bool Cell::isHollow() {
    //TODO: Implement this method    
    return (rand() % 3 == 0);
}

bool Cell::isWeak() {
    //TODO: Implement this method    
    return (rand() % 3 == 0);    
}

bool Cell::isWinningHole() {
    //TODO: Implement this method    
    return (rand() % 3 == 0);    
}
