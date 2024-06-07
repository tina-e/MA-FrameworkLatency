// #include "SDL.h"
#include <windows.h>
#include <signal.h>
#include <iostream>
// #include <GL/glut.h>
// #include <GL/gl.h>
#include <chrono>
#include <SDL2/SDL.h>

using namespace std;
using namespace chrono;

int WIDTH = 100;
int HEIGHT = 100;

// select SDL2 renderer: https://wiki.libsdl.org/SDL_RendererFlags
#define RENDERER SDL_RENDERER_ACCELERATED
// #define RENDERER SDL_RENDERER_PRESENTVSYNC

#define WINDOW_STYLE SDL_WINDOW_BORDERLESS

// #ifndef DRIVER
//  supported:
//  direct3d
//  opengl
//  opengles2
//  opengles
//  metal (apple)
//  software
#define DRIVER "direct3d"
// #endif

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
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, DRIVER);

    // create SDL2 window and renderer
    SDL_Window *window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, WINDOW_STYLE);
    SDL_SetWindowTitle(window, "framework");

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, RENDERER);
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0"); // sollte eig mit RENDERER schon abgedeckt sein
    SDL_RenderSetVSync(renderer, SDL_FALSE);

    // draw a black image
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (1)
    {
        // get input events via SDL
        while (SDL_PollEvent(&event))
        {
            // draw white image when mouse button is pressed
            // draw black image when mouse button is released
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }

    return 0;
}