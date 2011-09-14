//
//  main.cpp
//  Bloxorz
//
//  Created by Andrés Mejía on 07/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "KeyboardController.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

KeyboardController controller;

void display(void) {
    controller.refreshView();
}

void reshape(GLsizei w, GLsizei h) {
    controller.reshapeView((int)w, (int)h);
}

void specialKeys(int key, int x, int y) {
    controller.specialKeyPressed(key);
}

void keyboard(unsigned char key, int x, int y){
    controller.normalKeyPressed(key);
}


int main (int argc, char * argv[]) {
    printf("Executable path is %s\n", argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(AbstractView::WIDTH, AbstractView::HEIGHT);
    glutCreateWindow("Bloxorz");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    
    controller = KeyboardController();
    controller.prepare();

    glutMainLoop();
    
    controller.cleanUp();
    return 0;
}

