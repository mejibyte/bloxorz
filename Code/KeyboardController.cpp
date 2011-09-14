#include "KeyboardController.h"
#include <GL/glut.h> 

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
   if(key == GLUT_KEY_UP) {
	   board.moveTile(Board::Up);
    }
    if(key == GLUT_KEY_DOWN) {
		board.moveTile(Board::Down);
    }
    if(key == GLUT_KEY_LEFT) {
        board.moveTile(Board::Left);
    }
    if(key == GLUT_KEY_RIGHT) {
        board.moveTile(Board::Right);
    }
    glutPostRedisplay();
    printf("Special key pressed: %d.\n", key);
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

