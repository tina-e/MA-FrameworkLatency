#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <Windows.h> 

/* define the window size */
int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

//int WIDTH = 800;
//int HEIGHT = 800;

const int X_RECT = -WIDTH / 2 + 300;
const int Y_RECT = -HEIGHT / 2 + 300;
const int NUM_CUBES = 166;

GLfloat VERTICES[][3] = {
    {-200, -200, -200},
    {200, -200, -200},
    {200, 200, -200},
    {-200, 200, -200},
    {-200, -200, 200},
    {200, -200, 200},
    {200, 200, 200},
    {-200, 200, 200}
};

GLuint INDICES[][4] = {
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {5, 4, 7, 6},
    {4, 0, 3, 7},
    {3, 2, 6, 7},
    {4, 5, 1, 0}
};


GLfloat reds[NUM_CUBES];
GLfloat greens[NUM_CUBES];
GLfloat blues[NUM_CUBES];

GLfloat positionX[NUM_CUBES];
GLfloat positionY[NUM_CUBES];
GLfloat positionZ[NUM_CUBES];

GLfloat rotationX[NUM_CUBES];
GLfloat rotationY[NUM_CUBES];
GLfloat rotationZ[NUM_CUBES];
GLfloat rotationFactor[NUM_CUBES];
GLfloat rotationFactorTemp[NUM_CUBES];

GLfloat scalingX[NUM_CUBES];
GLfloat scalingY[NUM_CUBES];
GLfloat scalingZ[NUM_CUBES];

bool is_pressed = false;
bool do_redraw = false;

void setupCubes() {
    for (int i = 0; i < NUM_CUBES; i++) {
        reds[i] = (float)rand() / RAND_MAX;
        greens[i] = (float)rand() / RAND_MAX;
        blues[i] = (float)rand() / RAND_MAX;

        positionX[i] = (rand() % (WIDTH / 2 - (X_RECT)+1)) + X_RECT;
        positionY[i] = (rand() % (HEIGHT / 2 - (-HEIGHT / 2) + 1)) - HEIGHT / 2;
        positionZ[i] = rand() % 100;

        rotationX[i] = (float)rand() / RAND_MAX;
        rotationY[i] = (float)rand() / RAND_MAX;
        rotationZ[i] = (float)rand() / RAND_MAX;
        rotationFactor[i] = (float)rand() / RAND_MAX;

        scalingX[i] = (float)rand() / RAND_MAX;
        scalingY[i] = (float)rand() / RAND_MAX;
        scalingZ[i] = (float)rand() / RAND_MAX;
    }
}

void drawCube() {
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            glVertex3fv(VERTICES[INDICES[i][j]]);
        }
    }
    glEnd();
}

void input(int button, int state, int x, int y)
{
    if (button == 0 && state == GLUT_DOWN && !is_pressed)
    {
        is_pressed = true;
        setupCubes();
        glutSwapBuffers();
        glutPostRedisplay();
        glFlush();
    }
    else if (is_pressed)
    {
        is_pressed = false;
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
        glutPostRedisplay();
        glFlush();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    if (is_pressed) {
        for (int i = 0; i < NUM_CUBES; i++) {
            rotationFactorTemp[i] += rotationFactor[i];
            glPushMatrix();
            glTranslatef(positionX[i], positionY[i], positionZ[i]);
            glRotatef(rotationFactorTemp[i], rotationX[i], rotationY[i], rotationZ[i]);
            glScalef(scalingX[i], scalingY[i], scalingZ[i]);
            glColor3f(reds[i], greens[i], blues[i]);
            drawCube();
            glPopMatrix();
        }
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex2i(-WIDTH / 2, HEIGHT / 2);
        glVertex2i(X_RECT, HEIGHT / 2);
        glVertex2i(X_RECT, -Y_RECT);
        glVertex2i(-WIDTH / 2, -Y_RECT);
        glEnd();
    }

    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) 
{
    char* argv[1];
    int argc = 1;
    argv[0] = _strdup("framework");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("framework");
    
    glutFullScreen();
    glutGameModeString("1920x1080:16@500");
    glutEnterGameMode();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(input);

    glutMainLoop();
    return 0;
}