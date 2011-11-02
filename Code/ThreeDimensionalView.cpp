 #include "ThreeDimensionalView.h"

const int CUBE_SIDE = 10;

GLdouble cameraDistance = 200.0;
GLdouble incremento = 10.0;
GLdouble angulo = 0.0;
GLdouble incrementoAngulo = 0.1;

GLfloat mat_blue[] = { 0.1, 0.2, 0.8, 1.0 };
GLfloat mat_red[] = { 0.8, 0.2, 0.1, 1.0 };
GLfloat mat_green[] = { 0.1, 0.8, 0.1, 1.0 };
GLfloat mat_gray[] = {0.5, 0.5, 0.5, 1.0};

GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f}; //Color(0.2, 0.2, 0.2)
GLfloat light0color[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light0position[] = { 20.0, 100.0, 40.0, 0.0 };

ThreeDimensionalView::ThreeDimensionalView(){
    glClearColor(0, 0, 0, 1);
    glMatrixMode (GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);    
}

ThreeDimensionalView::ThreeDimensionalView(Board board){
    ThreeDimensionalView();
    setBoard(board);
}

void ThreeDimensionalView::setBoard(Board someBoard) {
    board = someBoard;
}

void ThreeDimensionalView::setPerspective() {
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 300.0);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ThreeDimensionalView::resetCamera() {
    cameraDistance = max(board.getRows(), board.getCols()) * CUBE_SIDE;
    printf("Camera distance = %lf\n", cameraDistance);
}

void ThreeDimensionalView::refresh(){
	puts("[VIEW] called refresh()");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	int rows = board.getRows();
	int cols = board.getCols();
    
    setPerspective();
    
    int middleX = rows * CUBE_SIDE / 2;
    int middleY = cols * CUBE_SIDE / 2;
    
    gluLookAt(middleX * 2, middleY, cameraDistance,         middleX, middleY, 0.0,     -1.0, 0.0, 0.0);
    glRotated(-15, 0, 1, 0);
    glRotated(-5, 0, 0, 1);
    
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0color);
    glLightfv(GL_LIGHT0, GL_POSITION, light0position);
    
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            Cell c = board.getCellAt(i, j);            
            if (c.isHollow()){
                // Do nothing
            }else if (c.isWeak()){
                drawCubeAt(i, j,    mat_green);
            }else if (c.isWinningHole()){
                drawCubeAt(i, j,    mat_red);
            } else {
                drawCubeAt(i, j,    mat_blue);
            }
        }
        
    }
    
    //aquí va el codigo del tile
	Tile t = board.getTile();
    vector<Cell> tileCells = t.getCurrentCells();
    for (int k = 0; k < tileCells.size(); ++k){
        const Cell &c = tileCells[k];
        printf("Tile is at <%d, %d>\n", c.getRow(), c.getColumn());
        drawTileAt(c.getRow(), c.getColumn(), t.isStandingUp());
    }

	glutSwapBuffers();    
}


void ThreeDimensionalView::reshape(GLsizei w, GLsizei h) {    
	glViewport(0, 0, w, h);
    setPerspective();
}

void ThreeDimensionalView::drawCubeAt(int row, int col, float color[]){

	GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat low_shininess[] = { 2.0 };
    
	glPushMatrix(); 
        glTranslatef(row * CUBE_SIDE + CUBE_SIDE / 2, col * CUBE_SIDE + CUBE_SIDE / 2, 0);
        glScalef(CUBE_SIDE, CUBE_SIDE, 0.2 * CUBE_SIDE);

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

        glutSolidCube(1.);       
    
	glPopMatrix();
    
}
void ThreeDimensionalView::drawTileAt(int row, int col, bool standingUp){
    GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat low_shininess[] = { 1.0 };
    GLfloat tile_color[] = { 0.0, 0.4, 1., 0.5 };
    
	glPushMatrix();
            glTranslatef(row * CUBE_SIDE + CUBE_SIDE / 2, col * CUBE_SIDE + CUBE_SIDE / 2, CUBE_SIDE / 2 + 0.2 * CUBE_SIDE);
            if (standingUp) {
                glTranslatef(0, 0, 0.2 * CUBE_SIDE);
            }
            
            glScalef(CUBE_SIDE, CUBE_SIDE, CUBE_SIDE + CUBE_SIDE * standingUp);
            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, tile_color);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
            
            glutSolidCube(1.);       

	glPopMatrix();
}

void ThreeDimensionalView::setMessage(const char * message) {
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, HEIGHT, 0.0);	// Left, Right, Bottom, Top corners    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    int textWidth = 0;
    for (const char * c = message; *c; c++){
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    int x = (WIDTH - textWidth) / 2;
    int y = HEIGHT / 2;
    
    glColor3f(0.8, 0.8, 0.8);
    glRasterPos2f(x, y);    
    for (const char * c = message; *c; c++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    glPopMatrix();
    glutSwapBuffers();
}

void ThreeDimensionalView::cameraUp() {
    cameraDistance -= incremento;
    cameraDistance = max(cameraDistance, 10.0);
    refresh();
}

void ThreeDimensionalView::cameraDown() {
    cameraDistance += incremento;
	refresh();
}

void ThreeDimensionalView::cameraRight() {
    angulo -= incrementoAngulo;
	refresh();
}

void ThreeDimensionalView::cameraLeft() {
    angulo += incrementoAngulo;
    refresh();
}

void ThreeDimensionalView::clearMessage() {
    refresh();
}