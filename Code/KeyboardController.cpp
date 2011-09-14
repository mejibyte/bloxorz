#include "KeyboardController.h"
#include <GL/glut.h> 

void KeyboardController::prepare() {
    printf("Preparing game from KeyboardController\n");
    board = Board("./boards/1.txt");
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
    if (!board.isLosingPosition()){
        printf("[CONTROLLER] Not losing position. Should refresh view.\n");
        view->setBoard(board);
        refreshView();
    } else {
        printf("[CONTROLLER] Losing position!\n");
    }
}

void KeyboardController::normalKeyPressed(unsigned char key){
    switch (key) {
      	case 27:
         exit(0);
         break;
      	case 'a':		
            board.moveTile(Board::Left);
            break;
      	case 's':		
            board.moveTile(Board::Down);
            break;
	case 'd':		
		board.moveTile(Board::Right);
		break;
	case 'w':		
		board.moveTile(Board::Up);
		break;
	}
	glutPostRedisplay();
    printf("%c was pressed.\n", key);
}

void KeyboardController::reshapeView(int newWidth, int newHeight){
    view->reshape(newWidth, newHeight);
}

