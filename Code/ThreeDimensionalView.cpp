#include "ThreeDimensionalView.h"

GLfloat ambient[] = { 0.0, 0.0, 0.0, 0.0 };  
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat position[] = { 5.0, 5.0, 5.0, 0.0 };

GLfloat mat_blue[] = { 0.1, 0.2, 0.8, 1.0 };
GLfloat mat_red[] = { 0.8, 0.2, 0.1, 1.0 };
GLfloat mat_green[] = { 0.1, 0.8, 0.1, 1.0 };
GLfloat mat_gray[] = {0.5, 0.5, 0.5, 1.0};

GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f}; //Color(0.2, 0.2, 0.2)
GLfloat light0color[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light0position[] = { 15.0, 5.0, 15.0, 0.0 };

GLfloat rowPos, colPos;

ThreeDimensionalView::ThreeDimensionalView(){
    glClearColor(0, 0, 0, 1);
    glMatrixMode (GL_PROJECTION);
    
}

ThreeDimensionalView::ThreeDimensionalView(Board board){
    ThreeDimensionalView();
    setBoard(board);
}

void ThreeDimensionalView::setBoard(Board someBoard) {
    board = someBoard;
}

void ThreeDimensionalView::refresh(){

	puts("[VIEW] called refresh()");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int rows = board.getRows();
	int cols = board.getCols();

	GLfloat scala = 1.;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0color);
    glLightfv(GL_LIGHT0, GL_POSITION, light0position);

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            Cell c = board.getCellAt(i, j);
			rowPos=i*scala;
			colPos=j*scala;
						
            if (c.isHollow()){
                drawCubeAt(i, j,    mat_gray);
            }else if (c.isWeak()){
                drawCubeAt(i, j,    mat_green);
            }else if (c.isWinningHole()){
                drawCubeAt(i, j,    mat_red);
            }else             
			drawCubeAt(rowPos,colPos, mat_blue);		
		  
        }
		
    }

	 glPopMatrix();
    
    glLightfv(GL_LIGHT0, GL_POSITION, position);

	
	//aquí va el codigo del tile
	/*Tile t = board.getTile();
    vector<Cell> tileCells = t.getCurrentCells();
    for (int k = 0; k < tileCells.size(); ++k){
        const Cell &c = tileCells[k];
        printf("Tile is at <%d, %d>\n", c.getRow(), c.getColumn());
        drawRectangleAt(c.getRow(), c.getColumn(), 0, 0, 1);
    }*/
	// Ejecutar los comandos 
	glutSwapBuffers();

}


void ThreeDimensionalView::reshape(GLsizei w, GLsizei h) {
    
	glViewport(0, 0, w, h);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
		glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 300.0);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawCubeAt(int row, int col, float color[]){

	GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat low_shininess[] = { 2.0 };

	glPushMatrix();
				//glRotatef((GLfloat) shoulderY, 0., 0., 1.); //para rotar el tablero
				glTranslatef(row, 0., col);
				glPushMatrix();
				glScalef(1., 0.5, 1.);

				glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    
				glutSolidCube(1.);       
				glPopMatrix();
				glEnd();
    
	glPopMatrix();

}

void ThreeDimensionalView::setMessage(const char * message) {
    int textWidth = 0;
    for (const char * c = message; *c; c++){
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    int x = (WIDTH - textWidth) / 2;
    int y = HEIGHT / 2;
    
    glColor3f(1, 1, 1);
    glRasterPos2f(x, y);    
    for (const char * c = message; *c; c++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    glutSwapBuffers();
}

void ThreeDimensionalView::clearMessage() {
    refresh();
}