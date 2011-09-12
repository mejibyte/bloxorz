#include "KeyboardController.h"

void KeyboardController::prepare() {
    printf("Preparing game from KeyboardController\n");
    board = Board("boards/1.txt");
    view = new TwoDimensionalView(board);
    
}

void KeyboardController::cleanUp() {
    delete view;
}

void KeyboardController::refreshView() {
    view->refresh();
}