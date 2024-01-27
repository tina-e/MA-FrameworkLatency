#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>

using namespace std;

float random_r[999] = { 0 };
float random_g[999] = { 0 };
float random_b[999] = { 0 };

float random_x[999] = { 0 };
float random_y[999] = { 0 };

bool pressed = false;


void calcRandoms() {
    for (int i = 0; i < 999; i++) {
        random_r[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        random_g[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        random_b[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        random_x[i] = -0.7 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-0.7))));
        random_y[i] = -0.7 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-0.7))));
    }
}

void drawRects() {
    for (int i = 0; i < 999; i++) {
        glColor3f(random_r[i], random_g[i], random_r[i]); glVertex2f(random_x[i], random_x[i]);
        glColor3f(random_r[i], random_g[i], random_r[i]); glVertex2f(random_x[i], random_y[i]);
        glColor3f(random_r[i], random_g[i], random_r[i]); glVertex2f(random_y[i], random_x[i]);
        glColor3f(random_r[i], random_g[i], random_r[i]); glVertex2f(random_y[i], random_x[i]);
        glColor3f(random_r[i], random_g[i], random_r[i]); glVertex2f(random_x[i], random_y[i]);
        glColor3f(random_r[i], random_g[i], random_r[i]); glVertex2f(random_y[i], random_y[i]);
    }
    glColor3f(1, 1, 1); glVertex2f(-1, 1);
    glColor3f(1, 1, 1); glVertex2f(-0.5, 1);
    glColor3f(1, 1, 1); glVertex2f(-1, 0.5);
    glColor3f(1, 1, 1); glVertex2f(-1, 0.5);
    glColor3f(1, 1, 1); glVertex2f(-0.5, 1);
    glColor3f(1, 1, 1); glVertex2f(-0.5, 0.5);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (!pressed) {
            pressed = true;
            calcRandoms();
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        pressed = false;
    }
}

int main() {
    if (!glfwInit()) {
        cerr << "Error initializing GLFW" << endl;
        return -1;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int width = mode->width;
    int height = mode->height;

    GLFWwindow* window = glfwCreateWindow(width, height, "framework", monitor, NULL);
    //glfwWindowHint(GLFW_DECORATED, 0);
    //GLFWwindow* window = glfwCreateWindow(width * 0.8, height * 0.8, "framework", NULL, NULL);
    
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (pressed) {
            glBegin(GL_TRIANGLES);
            drawRects();
            glEnd();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}
