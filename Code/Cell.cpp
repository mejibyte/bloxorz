#include "Cell.h"

Cell::Cell() {
}

Cell::Cell(int row, int col, bool empty, bool weak, bool winningHole) {
    int rowCell=row;
    int rowCol=col;
    bool floor=empty=true;
    bool wearFloor=false;   //por defecto todas las celdas serán solidas y al leer el board se cambiaran.
    bool floorWinningHole=false;
    
}

int Cell::getRow() const {
    
    return rowCell;
    
}

int Cell::getColumn() const {
       
    return rowCol;
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
