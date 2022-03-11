#include <iostream>
#include <string>

#include <glad/glad.h>
        
#include "Window.h"

#include "Time.h"
#include "Shader.h"
#include "Camera.h"

#define NR_POINT_LIGHTS 4

using namespace std;

void MouseCallback(GLFWwindow* window, double xpos, double ypos);

Camera MainCamera(glm::vec3(5.0f, 2.0f, 0.0f));

bool useMSAA = true;

bool firstMouse = true;
float lastX;
float lastY;

// settings
unsigned int SCR_WIDTH = 1800;
unsigned int SCR_HEIGHT = 1000;

int main()
{
    Window MainWindow;

    // glfw: initialize and configure
    // ------------------------------
    MainWindow.Initialize();
    if (!MainWindow.Create("LE", SCR_WIDTH, SCR_HEIGHT))
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Check for max number of vertex attributes
    int numAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);
    std::cout << "Maximum number of vertex attributes supported: " << numAttributes << std::endl;
    // build and compile our shader program
    // ------------------------------------


    bool show_demo_window = true;
    bool show_another_window = false;

    float f = 0.0f;

    glm::vec3 pointLightPositions[] = 
    {
        glm::vec3(0.0f,  7.0f,  0.0f),
    };

    glfwSetInputMode(MainWindow.GetInstance(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(MainWindow.GetInstance(), MouseCallback);

    glBindFramebuffer(GL_FRAMEBUFFER, 0); 

    Shader::initUniformBuffer();

    glEnable(GL_DEPTH_TEST);


    while (!MainWindow.ShouldClose())
    {

        // input
        MainWindow.ProcessInput();
        MainWindow.RecalculateSize();

        MainWindow.SwapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void CameraMove(GLFWwindow* window, double deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        MainCamera.ProcessMovement(Enum::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        MainCamera.ProcessMovement(Enum::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        MainCamera.ProcessMovement(Enum::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        MainCamera.ProcessMovement(Enum::RIGHT, deltaTime);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        MainCamera.ProcessMouseMovement(xoffset, yoffset);
    }
}
