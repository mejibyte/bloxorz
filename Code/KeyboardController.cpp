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
void KeyboardController::specialKeyPressed(int key){
    // TODO: Do something here.
    printf("Special key pressed: %d.\n", key);
}

void KeyboardController::normalKeyPressed(unsigned char key){
    // TODO: Do something here.
    printf("%c was pressed.\n", key);
}

