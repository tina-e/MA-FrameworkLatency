// code based on schmid & wimmer

//#include "SDL.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <signal.h>
#include <windows.h>

int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
bool running = true;

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

    SDL_Init(SDL_INIT_VIDEO); // maybe we have to reduce this?

    SDL_Window* window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(0); // 0 immediate, 1 vsync, -1 adaptive sync

    //glewExperimental = GL_TRUE;
    glewInit();


//#ifdef DOUBLEBUF
//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//#endif


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    glClearColor(1.0, 1.0, 1.0, 1.0);
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    glClearColor(0.0f, 0.0f, 0.0, 1.0f);
                }
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
