// this application was refined using ChatGPT
#include <GL/glut.h>
#include <signal.h>
#include <iostream>

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    exit(sig);
}

int windowWidth = (int) 1920 * 0.8;
int windowHeight = (int) 1200 * 0.8;

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

int main(int argc, char** argv) {
    signal(SIGINT, signalHandler);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("framework");
    // glutFullScreen();


    HWND frameworkWindow = FindWindow(NULL, "framework");
    if (frameworkWindow != NULL) {
        std::cout << "found" << std::endl;
        SetWindowPos(frameworkWindow, NULL, 0, 0, windowWidth, windowHeight, SWP_NOZORDER | SWP_NOSIZE);
        SetForegroundWindow(frameworkWindow);
    }
    else {
        std::cerr << "no window named framework" << std::endl;
    }


    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}