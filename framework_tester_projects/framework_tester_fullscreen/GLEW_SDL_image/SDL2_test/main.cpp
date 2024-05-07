//#include "SDL.h"
#include <GL/glew.h>
#include <signal.h>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

bool is_pressed = false;
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
    SDL_Window* window = SDL_CreateWindow("framework", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(0); // 0 immediate, 1 vsync, -1 adaptive sync

    //glewExperimental = GL_TRUE;
    glewInit();

    SDL_Surface* image = IMG_Load("noise.png");

    // Create a texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the image data into the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

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
                    is_pressed = true;
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    is_pressed = false;
                }
            }
        }
        if (is_pressed)
        {
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
            glEnd();
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
