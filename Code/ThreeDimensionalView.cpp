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

GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f}; 
GLfloat light0color[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light0position[] = { 20.0, 100.0, 40.0, 0.0 };

// Texture handler
GLuint texture;
GLuint textureFloor;


ThreeDimensionalView::ThreeDimensionalView(){
    glClearColor(0, 0, 0, 1);
    glMatrixMode (GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    texture = loadTexture("metal.bmp", true);
    textureFloor = loadTexture("tex_wood.bmp", true);
    
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
    glEnable(GL_POLYGON_SMOOTH);
    
    
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
                // Draw nothing at the winning hole.
            } else {
                drawCubeAt(i, j,    mat_blue);
            }
        }
        
    }
    
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
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureFloor);
	glPushMatrix(); 
        glTranslatef(row * CUBE_SIDE + CUBE_SIDE / 2, col * CUBE_SIDE + CUBE_SIDE / 2, 0);
        glScalef(CUBE_SIDE, CUBE_SIDE, 0.2 * CUBE_SIDE);

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

        glutSolidCube(1.);   
    
	glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void ThreeDimensionalView::drawTileAt(int row, int col, bool standingUp){
    
    GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat low_shininess[] = { 1.0 };
    GLfloat tile_color[] = { 0.0, 0.4, 1., 0.5 };
    
	glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTranslatef(row * CUBE_SIDE + CUBE_SIDE / 2, col * CUBE_SIDE + CUBE_SIDE / 2, CUBE_SIDE / 2 + 0.2 * CUBE_SIDE);
            if (standingUp) {
                glTranslatef(0, 0, 0.2 * CUBE_SIDE);
            }
            
            glScalef(CUBE_SIDE, CUBE_SIDE, CUBE_SIDE + CUBE_SIDE * standingUp);
            glTexCoord2f(1.0, 0.0);    

            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, tile_color);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
            
            solidCubeWithTexture(1.);       
            glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    
        

}

void ThreeDimensionalView::setMessage(const char * message) {
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, HEIGHT, 0.0);	// Left, Right, Bottom, Top corners    
    
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_LIGHTING);
    
    glLoadIdentity();
    int textWidth = 0;
    for (const char * c = message; *c; c++){
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    int x = (WIDTH - textWidth) / 2;
    int y = 30;
    
    glColor3f(1.0, 1.0, 1.0);
    
    glRasterPos2f(x, y);    
    for (const char * c = message; *c; c++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    glEnable(GL_LIGHTING);
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
    cameraDistance = min(cameraDistance, 200.0);
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

void ThreeDimensionalView::solidCubeWithTexture(GLfloat size){
    static GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;
    
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
    
    for (i = 5; i >= 0; i--) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        
        
        
        glTexCoord2d(0.0,0.0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2d(0.0,1.0);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2d(1.0,1.0);        
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2d(1.0,0.0);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void ThreeDimensionalView::loadTextureFromFile(char *filename)
{    
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
    
	RgbImage theTexMap( filename );
    
	// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
	//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    
}


GLuint ThreeDimensionalView::loadTexture( const char * filename, bool wrap ) {
    GLuint ans;
    
    glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
    RgbImage theTexMap( filename );
    
    
    // allocate a texture name
    glGenTextures( 1, &ans );
    
    // select our current texture
    glBindTexture( GL_TEXTURE_2D, ans );
    
    // select modulate to mix texture with color for shading
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    
    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    wrap ? GL_REPEAT : GL_CLAMP );
    
    // build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    
    return ans;
}

