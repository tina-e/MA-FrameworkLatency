#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <Windows.h>


int WIDTH = GetSystemMetrics(SM_CXSCREEN);
int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

//const int WIDTH = 1920;
//const int HEIGHT = 1080;
const int X_RECT = -WIDTH / 2 + 300;
const int Y_RECT = -HEIGHT / 2 + 300;
const int NUM_CUBES = 166;

GLfloat VERTICES[][3] = {
        {-200, -200, -200}, 
        {200, -200, -200},  
        {200, 200, -200},  
        {-200, 200, -200},
        {-200, -200, 200},  
        {200, -200, 200},   
        {200, 200, 200},  
        {-200, 200, 200} 
};

GLuint INDICES[][4] = {
    {0, 1, 2, 3}, 
    {1, 5, 6, 2}, 
    {5, 4, 7, 6}, 
    {4, 0, 3, 7}, 
    {3, 2, 6, 7}, 
    {4, 5, 1, 0}  
};


GLfloat reds[NUM_CUBES];
GLfloat greens[NUM_CUBES];
GLfloat blues[NUM_CUBES];

GLfloat positionX[NUM_CUBES];
GLfloat positionY[NUM_CUBES];
GLfloat positionZ[NUM_CUBES];

GLfloat rotationX[NUM_CUBES];
GLfloat rotationY[NUM_CUBES];
GLfloat rotationZ[NUM_CUBES];
GLfloat rotationFactor[NUM_CUBES];
GLfloat rotationFactorTemp[NUM_CUBES];

GLfloat scalingX[NUM_CUBES];
GLfloat scalingY[NUM_CUBES];
GLfloat scalingZ[NUM_CUBES];


void setupCubes() {
    for (int i = 0; i < NUM_CUBES; i++) {
        reds[i] = (float)rand() / RAND_MAX;
        greens[i] = (float)rand() / RAND_MAX;
        blues[i] = (float)rand() / RAND_MAX;

        positionX[i] = (rand() % (WIDTH / 2 - (X_RECT) + 1)) + X_RECT;
        positionY[i] = (rand() % (HEIGHT / 2 - (-HEIGHT / 2) + 1)) - HEIGHT / 2;
        positionZ[i] = rand() % 100;

        rotationX[i] = (float) rand() / RAND_MAX;
        rotationY[i] = (float) rand() / RAND_MAX;
        rotationZ[i] = (float) rand() / RAND_MAX;
        rotationFactor[i] = (float)rand() / RAND_MAX;

        scalingX[i] = (float)rand() / RAND_MAX;
        scalingY[i] = (float)rand() / RAND_MAX;
        scalingZ[i] = (float)rand() / RAND_MAX;
    }
}

void drawCube() {
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            glVertex3fv(VERTICES[INDICES[i][j]]);
        }
    }
    glEnd();
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("framework", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL); // SDL_WINDOW_FULLSCREEN_DESKTOP for desktop fullscreen
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(0);
    
    glewInit();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho((GLdouble)-(WIDTH / 2), (GLdouble)WIDTH / 2, (GLdouble)HEIGHT / 2, (GLdouble)-HEIGHT / 2, -1.0, 1000);

    SDL_Event event;
   
    float angle = 0.1f;
    bool wasPressed = false;
    bool windowClosed = false;
    while (!windowClosed) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                windowClosed = true;
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    setupCubes();
                    wasPressed = true;
                }
            }

            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    wasPressed = false;
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (wasPressed) {
            for (int i = 0; i < NUM_CUBES; i++) {
                rotationFactorTemp[i] += rotationFactor[i];
                glPushMatrix();
                glTranslatef(positionX[i], positionY[i], positionZ[i]);
                glRotatef(rotationFactorTemp[i], rotationX[i], rotationY[i], rotationZ[i]);
                glScalef(scalingX[i], scalingY[i], scalingZ[i]);
                glColor3f(reds[i], greens[i], blues[i]);
                drawCube();
                glPopMatrix();
            }
            glColor3f(1, 1, 1);
            glBegin(GL_QUADS);
            glVertex2i(-WIDTH / 2, -HEIGHT / 2);
            glVertex2i(X_RECT, -HEIGHT / 2);
            glVertex2i(X_RECT, Y_RECT);
            glVertex2i(-WIDTH / 2, Y_RECT);
            glEnd();
        }
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

