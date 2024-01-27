#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
int r = 0;
int g = 0;
int b = 0;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        r = 1;
        g = 1;
        b = 1;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        r = 0;
        g = 0;
        b = 0;
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
        glClearColor(r, g, b, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}
