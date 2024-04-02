// code based on schmid & wimmer

#include "SDL.h"
#include <GL/glew.h>
#include <cstdlib>
#include <signal.h>
#include <windows.h>

int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

bool running = true;

bool is_pressed = false;
bool do_redraw = true;

const int n_rects = 1000;
int n_horizontal = 10;
int n_vertical = 10;
int rect_w = WIDTH / n_horizontal;
int rect_h = HEIGHT / n_vertical;

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    running = false;
    SDL_Quit();
    exit(sig);
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL); // SDL_WINDOW_FULLSCREEN for exclusive fullscreen
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(0); // 0 immediate, 1 vsync, -1 adaptive sync

    glewInit();
    SDL_Surface* image = IMG_Load("noise.png");


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    SDL_Event event;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)WIDTH, (GLdouble)HEIGHT, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    //glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    while (running)
    {
        bool do_redraw = false;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    glClear(GL_COLOR_BUFFER_BIT);
                    for (int i = 0; i < 1000; i++)
                    {
                        float r = (float)rand() / RAND_MAX;
                        float g = (float)rand() / RAND_MAX;
                        float b = (float)rand() / RAND_MAX;
                        glColor3f(r, g, b);

                        int x = (rand() % WIDTH/2) + WIDTH/2;
                        int y = rand() % HEIGHT;
                        int width = rand() % (WIDTH - x);
                        int height = rand() % (HEIGHT - y);

                        glBegin(GL_QUADS);
                        glVertex2i(x, y);
                        glVertex2i(x + width, y);
                        glVertex2i(x + width, y + height);
                        glVertex2i(x, y + height);
                        glEnd();
                    }

                    glColor3f(1, 1, 1);
                    glBegin(GL_QUADS);
                    glVertex2i(0, 0);
                    glVertex2i(300, 0);
                    glVertex2i(300, 300);
                    glVertex2i(0, 300);
                    glEnd();
                    glFlush();
                    SDL_GL_SwapWindow(window);
                    glClear(GL_COLOR_BUFFER_BIT);
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    glClearColor(0.0f, 0.0f, 0.0, 1.0f);
                    SDL_GL_SwapWindow(window);
                    glClear(GL_COLOR_BUFFER_BIT);
                }
            }
        }

        //SDL_GL_SwapWindow(window);
    }

    return 0;
}
