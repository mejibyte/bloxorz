#include "Tile.h"

Tile::Tile(){
    cells = vector<Cell>(0);
}

bool Tile::isStandingUp() {
    // TODO: Implement this method
    return false;
}

bool isLayingDown() {
    // TODO: Implement this method
    return true;
}

vector<Cell> Tile::getCurrentCells() {
    return cells;
}

void Tile::addCell(Cell someCellWhereTheTileIs) {
    cells.push_back(someCellWhereTheTileIs);
}