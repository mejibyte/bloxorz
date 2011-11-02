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
#include "Falling.h"
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
void idle(void){
    
    freeFalling();
    
}


int main (int argc, char * argv[]) {
    if (argc < 2){
        fprintf(stderr, "You need to pass the directory where the boards are as a parameter.\n");
        fprintf(stderr, "  Example: %s \"%s\"\n", argv[0], "~/Users/Andy/Games/Bloxorz/Boards");
        exit(-1);
    }
    
    printf("Executable path is %s\n", argv[0]);
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(AbstractView::WIDTH, AbstractView::HEIGHT);
    glutIdleFunc(idle);
    glutCreateWindow("Bloxorz");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    
    controller = KeyboardController(string(argv[1]));

    glutMainLoop();
    
    
    controller.cleanUp();
    return 0;
}

