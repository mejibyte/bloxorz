#include "Tile.h"

Tile::Tile(){
    cells = vector<Cell>(0);
}

bool Tile::isStandingUp() const {
    return cells.size() == 1;
}

bool Tile::isLayingDown() const {
    return cells.size() > 1;
}

vector<Cell> Tile::getCurrentCells() const {
    return cells;
}

void Tile::addCell(Cell someCellWhereTheTileIs) {
    cells.push_back(someCellWhereTheTileIs);
}

void Tile::clearCells() {
    cells.clear();
}