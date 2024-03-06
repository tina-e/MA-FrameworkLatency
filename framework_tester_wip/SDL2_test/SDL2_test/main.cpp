#include "SDL.h"
#include <windows.h>
#include <signal.h>
#include <iostream>
//#include <GL/glut.h>
//#include <GL/gl.h>
#include <chrono>

using namespace std;
using namespace chrono;
//typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALFARPROC)(int);
//typedef int(APIENTRY* PFNWGLGETSWAPINTERVALEXTPROC)();
//PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = nullptr;
//PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = nullptr;

// screen size
//int WIDTH = GetSystemMetrics(SM_CXSCREEN);
//int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
int WIDTH = 100;
int HEIGHT = 100;

// select SDL2 renderer: https://wiki.libsdl.org/SDL_RendererFlags
//#define RENDERER SDL_RENDERER_ACCELERATED
#define RENDERER SDL_RENDERER_PRESENTVSYNC

#define WINDOW_STYLE SDL_WINDOW_BORDERLESS
// #define WINDOW_STYLE SDL_WINDOW_FULLSCREEN_DESKTOP

//#ifndef DRIVER
// supported:
// direct3d
// opengl
// opengles2
// opengles
// metal (apple)
// software
#define DRIVER "software"
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
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, DRIVER);

    // create SDL2 window and renderer
    SDL_Window *window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, WINDOW_STYLE);
    SDL_SetWindowTitle(window, "framework");

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, RENDERER);
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"); // sollte eig mit RENDERER schon abgedeckt sein
    SDL_RenderSetVSync(renderer, SDL_TRUE);
    
    // draw a black image
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;

    /*const char *vsync = SDL_GetHint(SDL_HINT_RENDER_VSYNC);
    bool vsyncEnabled = std::strcmp(vsync, "1") == 0;
    std::cout << vsync << std::endl;*/
    /*bool state = false;
    for (int i = 0; i < 5000; i++) {
        state = !state;
        uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        if (state) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        else SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

        cout << 1000000 / (end_time - start_time) << endl;
    }*/




    //wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
    //wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");

    //if (wglSwapIntervalEXT == nullptr) {
    //    std::cerr << "wglSwapIntervalEXT not supported!" << std::endl;
    //    return 1;
    //}

    //HWND frameworkWindow = FindWindow(NULL, L"framework");
    //HDC hdc = GetDC(frameworkWindow);
    //HGLRC hglrc = wglCreateContext(hdc);
    //wglMakeCurrent(hdc, hglrc);

    //int vsyncEnabled = wglGetSwapIntervalEXT();
    ////std::cout << "Vsync is currently " << (vsyncEnabled == 1 ? "enabled" : "disabled") << std::endl;

    //wglSwapIntervalEXT(1);

    //vsyncEnabled = wglGetSwapIntervalEXT();
    // std::cout << "Vsync is currently " << (vsyncEnabled == 1 ? "enabled" : "disabled") << std::endl;


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