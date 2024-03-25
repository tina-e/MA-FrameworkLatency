#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <SOIL/SOIL.h>

/* define the window size */
int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

unsigned char* image;
bool is_pressed = false;


void setupTexture()
{
    glEnable(GL_TEXTURE_2D);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void drawTexture()
{
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void display()
{

}

void input(int button, int state, int x, int y)
{
    if (button == 0 && state == GLUT_DOWN && !is_pressed)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        is_pressed = true;
        setupTexture();
        drawTexture();
    }
    else if (is_pressed)
    {
        is_pressed = false;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
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

    image = SOIL_load_image("noise.png", &WIDTH, &HEIGHT, 0, SOIL_LOAD_RGB);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("framework");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutFullScreen();

    glutGameModeString("1920x1080:16@500");
    glutEnterGameMode();

    glutDisplayFunc(display);
    glutMouseFunc(input);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();

    glutMainLoop();
    return 0;
}