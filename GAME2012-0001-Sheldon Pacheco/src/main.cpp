#include "GLFW/glfw3.h"  
#include <glad/glad.h>
#include "iostream"
#include "random"
#include "cstdlib"
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
float Random(float min, float max)
{
    return min + (rand() / ((float)RAND_MAX / (max - min)));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main(void)
{
    

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pog", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Load OPENGL 4.6 */
    gladLoadGL();
    glfwSetKeyCallback(window, key_callback);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.22f, 0.49f, 0.17f, 1.0f);
        float x = Random(0.0f, SCREEN_WIDTH);
        float y = Random(0.0f, SCREEN_HEIGHT);
        glfwSetCursorPos(window, x, y);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const char* name = glfwGetKeyName(key, scancode);
    if (action == GLFW_PRESS)
        printf("%s\n", name);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}