#include "Tile.h"

Tile::Tile(){
    cells = vector<Cell>(0);
}

bool Tile::isStandingUp() {
    return cells.size() == 1;
}

bool Tile::isLayingDown() {
    return cells.size() > 1;
}

vector<Cell> Tile::getCurrentCells() {
    return cells;
}

void Tile::addCell(Cell someCellWhereTheTileIs) {
    cells.push_back(someCellWhereTheTileIs);
}