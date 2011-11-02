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
    //view = new TwoDimensionalView(board);    
    view = new ThreeDimensionalView(board);
    view->resetCamera();
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
        if (loadBoard(++currentBoard)){
            view->setBoard(board);
            view->resetCamera();
            refreshView();            
        }
        
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
            if (isThereNextLevel()) {
                view->setMessage("Good job! Press any key to load next level.");
            } else {
                // End of game
                view->setMessage("Congratulations, you completed the game! Now go get a beer. Press ESC to exit.");                
            }
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
      	case 'w':		
            specialKeyPressed(GLUT_KEY_UP);
            break;
      	case 's':		
            specialKeyPressed(GLUT_KEY_DOWN);
            break;
        case 'd':		
            specialKeyPressed(GLUT_KEY_RIGHT);
            break;
        case 'a':		
            specialKeyPressed(GLUT_KEY_LEFT);
            break;
        case 'u':		
            view->cameraUp();
            break;
        case 'j':		
            view->cameraDown();
            break;
        case 'h':		
            view->cameraLeft();
            break;
        case 'k':		
            view->cameraRight();
            break;
       
	}
}

void KeyboardController::reshapeView(int newWidth, int newHeight){
    view->reshape(newWidth, newHeight);
}

bool KeyboardController::loadBoard(int boardNumber) {
    stringstream sin;
    sin << boardsDir << boardNumber << ".txt";
    
    struct stat st;
    if(stat(sin.str().c_str(), &st) == 0) {
        printf("[CONTROLLER] Loading board %s\n", sin.str().c_str());
        board = Board(sin.str());
        return true;
    } else {
        return false;
    }
}

bool KeyboardController::isThereNextLevel() {
    stringstream sin;
    sin << boardsDir << currentBoard + 1 << ".txt";
    struct stat st;
    return (stat(sin.str().c_str(), &st) == 0);
}
