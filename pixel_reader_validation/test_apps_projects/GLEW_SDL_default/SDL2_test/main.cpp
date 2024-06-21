#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <signal.h>
#include <windows.h>
#include <chrono>

using namespace std;
using namespace chrono;

int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN) - 1;


int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO); 
    SDL_Window* window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(0); // 0 immediate, 1 vsync, -1 adaptive sync
    //glewExperimental = GL_TRUE;
    glewInit();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    int numClicks = 0;
    bool isWhite = false;
    bool running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                numClicks++;
                if (numClicks == 3) {
                    glClearColor(1.0, 1.0, 1.0, 1.0);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(window);
                    Sleep(50);
                    glClearColor(0.0, 0.0, 0.0, 1.0);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(window);
                    long start = (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count();
                    printf("start:-1:%ld\n", start);
                    fflush(stdout);
                    for (int i = 0; i <= 10; i++) {
                        while (true) {
                            long current_time = (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count();
                            if (current_time - start >= i * 50000) { // change color vlaue every 200ms
                                /*if (isWhite) {
                                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                }
                                else {
                                    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                                }
                                glClear(GL_COLOR_BUFFER_BIT);
                                SDL_GL_SwapWindow(window);
                                isWhite = !isWhite;*/
                                printf("render_start:%d:%ld\n", i, (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count());
                                fflush(stdout);
                                glClearColor(i * 0.1, i * 0.1, i * 0.1, 1.0);
                                glClear(GL_COLOR_BUFFER_BIT);
                                SDL_GL_SwapWindow(window);
                                printf("render_stop:%d:%ld\n", i, (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count());
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
