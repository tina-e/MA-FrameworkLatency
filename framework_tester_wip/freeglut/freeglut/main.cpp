// this application was refined using ChatGPT
#include <GL/glut.h>
#include <signal.h>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>

using namespace std;

// typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALFARPROC)(int);
// typedef int(APIENTRY* PFNWGLGETSWAPINTERVALEXTPROC)();
// PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = nullptr;
// PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = nullptr;

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    exit(sig);
}

// int WIDTH = GetSystemMetrics(SM_CXSCREEN);
// int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
int WIDTH = 100;
int HEIGHT = 100;

int colorR = 0;
int colorG = 0;
int colorB = 0;

void display()
{
    glClearColor(colorR, colorG, colorB, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    // glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        colorR = 1.0;
        colorG = 1.0;
        colorB = 1.0;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        colorR = 0.0;
        colorG = 0.0;
        colorB = 0.0;
    }
    glutPostRedisplay();
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    signal(SIGINT, signalHandler);

    char *argv[1];
    int argc = 1;
    argv[0] = _strdup("framework");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("framework");
    // glutFullScreen();
    // glutGameModeString("1920x1080:16@500");
    // glutEnterGameMode();

    // HWND frameworkWindow = FindWindow(NULL, L"framework");
    // if (frameworkWindow != NULL)
    //{
    //     MoveWindow(frameworkWindow, -10, -32, WIDTH, HEIGHT, FALSE);
    //     BringWindowToTop(frameworkWindow);
    //     SetForegroundWindow(frameworkWindow);
    //     SetFocus(frameworkWindow);
    // }

    /*wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
    wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");*/

    // if (wglSwapIntervalEXT == nullptr) {
    //     std::cerr << "wglSwapIntervalEXT not supported!" << std::endl;
    //     return 1;
    // }

    // HWND frameworkWindow = FindWindow(NULL, L"framework");
    // HDC hdc = GetDC(frameworkWindow);
    // HGLRC hglrc = wglCreateContext(hdc);
    // wglMakeCurrent(hdc, hglrc);

    // int vsyncEnabled = wglGetSwapIntervalEXT();
    ////std::cout << "Vsync is currently " << (vsyncEnabled == 1 ? "enabled" : "disabled") << std::endl;

    // wglSwapIntervalEXT(1);

    // vsyncEnabled = wglGetSwapIntervalEXT();
    // std::cout << "Vsync is currently " << (vsyncEnabled == 1 ? "enabled" : "disabled") << std::endl;

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}