#include "Tile.h"

bool Tile::isStandingUp() {
    // TODO: Implement this method
    return false;
}

bool isLayingDown() {
    // TODO: Implement this method
    return true;
}

vector<Cell> Tile::getCurrentCells() {
    // TODO: Implement this method
    vector<Cell> ans;
    ans.push_back(Cell(1, 1, false, false, false));
    ans.push_back(Cell(1, 2, false, false, false));
    return ans;
}

