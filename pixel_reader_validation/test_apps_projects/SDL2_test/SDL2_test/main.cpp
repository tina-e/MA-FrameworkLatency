//#include "SDL.h"
#include <windows.h>
#include <signal.h>
#include <iostream>
//#include <GL/glut.h>
//#include <GL/gl.h>
#include <chrono>
#include <SDL2/SDL.h>

using namespace std;
using namespace chrono;

// screen size
int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);


// select SDL2 renderer: https://wiki.libsdl.org/SDL_RendererFlags
#define RENDERER SDL_RENDERER_ACCELERATED
//#define RENDERER SDL_RENDERER_PRESENTVSYNC

//#define WINDOW_STYLE SDL_WINDOW_BORDERLESS
#define WINDOW_STYLE SDL_WINDOW_FULLSCREEN

//#ifndef DRIVER
// supported:
// direct3d
// opengl
// opengles2
// opengles
// metal (apple)
// software
#define DRIVER "OpenGL"
//#endif

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    SDL_Quit();
    exit(sig);
}

int main(int argc, char **argv)
{
    signal(SIGINT, signalHandler);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_bool res = SDL_SetHint(SDL_HINT_RENDER_DRIVER, DRIVER);
    //const char* driver = SDL_GetHint(SDL_HINT_RENDER_DRIVER);
    //const char* driver2 = SDL_GetCurrentVideoDriver();

    // create SDL2 window and renderer
    SDL_Window *window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, WINDOW_STYLE);
    SDL_SetWindowTitle(window, "framework");

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, RENDERER);
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0"); // sollte eig mit RENDERER schon abgedeckt sein
    SDL_RenderSetVSync(renderer, SDL_FALSE);
    //SDL_RendererInfo rendererInfo;
    //SDL_GetRendererInfo(renderer, &rendererInfo);
    
    // draw a black image
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    int numClicks = 0;
    bool isWhite = false;
    bool running = 1;
    int color = 0;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                numClicks++;
                if (numClicks == 3) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    long start = (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count();
                    printf("start:0:%ld\n", start);
                    fflush(stdout);
                    for (int i = 1; i <= 255; i++) {
                        while (true) {
                            long current_time = (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count();
                            if (current_time - start >= i * 50000) {
                                long start = (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count();

                                SDL_SetRenderDrawColor(renderer, i, i, i, 255);
                                SDL_RenderClear(renderer);
                                SDL_RenderPresent(renderer);

                                long stop = (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count();
                                printf("render_start:%d:%ld\n", i, start);
                                printf("render_stop:%d:%ld\n", i, stop);
                                fflush(stdout);
                                break;
                            }
                        }
                    }
                    running = 0;
                }
            }
        }
    }
    SDL_Quit();
    return 0;
}