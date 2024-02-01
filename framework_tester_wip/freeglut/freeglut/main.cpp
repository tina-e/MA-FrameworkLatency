// this application was refined using ChatGPT
#include <GL/glut.h>
#include <signal.h>
#include <iostream>

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    exit(sig);
}

int windowWidth = (int) 1920;
int windowHeight = (int) 1200;

int colorR = 0;
int colorG = 0;
int colorB = 0;

void display() {
    glClearColor(colorR, colorG, colorB, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        colorR = 1.0;
        colorG = 1.0;
        colorB = 1.0;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        colorR = 0.0;
        colorG = 0.0;
        colorB = 0.0;
    }
    glutPostRedisplay();
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    signal(SIGINT, signalHandler);

    char* argv[1];
    int argc = 1;
    argv[0] = _strdup("framework");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA ); // double buffering (??)
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("framework");
    // ?? glSwapIntervalEXT(1);
    glutFullScreen();

    /*HWND frameworkWindow = FindWindow(NULL, L"framework");
    if (frameworkWindow != NULL) {
        MoveWindow(frameworkWindow, -50, -50, windowWidth, windowHeight, FALSE);
        BringWindowToTop(frameworkWindow);
        SetForegroundWindow(frameworkWindow);
        SetFocus(frameworkWindow);
    }*/

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}