#include "KeyboardController.h"

KeyboardController::KeyboardController() {
    view = NULL;
}

KeyboardController::KeyboardController(string boardsDir) {
    printf("[CONTROLLER] Creating KeyboardController\n");
    
    assert(boardsDir.size() > 0);
    if (boardsDir[boardsDir.size() - 1] != '/') boardsDir += '/';
    this->boardsDir = boardsDir;
    
    currentBoard = 1;
    loadBoard(currentBoard);
    view = new TwoDimensionalView(board);    
}

void KeyboardController::cleanUp() {
    delete view;
}

void KeyboardController::refreshView() {
    view->refresh();
}
void KeyboardController::specialKeyPressed(int key){
    printf("Special key pressed: %d.\n", key);
    if (board.isWinningPosition()){
        printf("[CONTROLLER] Winning position! Load next level\n");
    } else if (board.isLosingPosition()) {
        printf("[CONTROLLER] Losing position! Restart level\n");
        loadBoard(currentBoard);
        view->setBoard(board);
        refreshView();
    } else {
        printf("[CONTROLLER] You haven't lost. Should refresh view.\n");
        if (key == GLUT_KEY_UP){
            printf("[CONTROLLER] Pressed UP key.\n");
            board.moveTile(Board::Up);
            
        } else if (key == GLUT_KEY_DOWN) {
            printf("[CONTROLLER] Pressed DOWN key.\n");        
            board.moveTile(Board::Down);        
            
        } else if (key == GLUT_KEY_LEFT) {
            printf("[CONTROLLER] Pressed LEFT key.\n");        
            board.moveTile(Board::Left);                
            
        } else if (key == GLUT_KEY_RIGHT) {
            printf("[CONTROLLER] Pressed RIGHT key.\n");        
            board.moveTile(Board::Right);        
        }
        view->setBoard(board);
        refreshView();
        if (board.isLosingPosition()){
            view->setMessage("You lost! Press any key to restart.");            
        }
        if (board.isWinningPosition()) {
            view->setMessage("Good job! Press any key to load next level.");
        }
    }
}

void KeyboardController::normalKeyPressed(unsigned char key){
    printf("[CONTROLLER] %c was pressed.\n", key);
    if (board.isLosingPosition()) {
        specialKeyPressed(-1);
        return;
    }
    switch (key) {
      	case 27:
            exit(0); //ESC
            break;
      	case 'a':		
            specialKeyPressed(GLUT_KEY_UP);
            break;
      	case 's':		
            specialKeyPressed(GLUT_KEY_DOWN);
            break;
        case 'd':		
            specialKeyPressed(GLUT_KEY_RIGHT);
            break;
        case 'w':		
            specialKeyPressed(GLUT_KEY_LEFT);
            break;
	}
}

void KeyboardController::reshapeView(int newWidth, int newHeight){
    view->reshape(newWidth, newHeight);
}

void KeyboardController::loadBoard(int boardNumber) {
    stringstream sin;
    sin << boardsDir << boardNumber << ".txt";
    printf("[CONTROLLER] Loading board %s\n", sin.str().c_str());
    board = Board(sin.str());
}
