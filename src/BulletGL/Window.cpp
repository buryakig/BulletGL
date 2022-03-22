#include "Window.h"

Window::Window()
{
	instance = NULL;
}

Window::Window(int w, int h)
{
	instance = NULL;
    width = w;
    height = h;
}

void Window::Initialize()
{
	glfwInit();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(this->instance);
}

bool Window::Create(const std::string& name, const int& width, const int& height)
{
    this->width = width;
    this->height = height;
    this->aspectRatio = (float)width / height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    this->instance = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (this->instance == NULL)
    {
        glfwTerminate();
        return false;
    }

    SetCurrent();
    glfwSetFramebufferSizeCallback(this->instance, FramebufferResizeCallback);
    return true;
}

void Window::SetCurrent()
{
    glfwMakeContextCurrent(this->instance);
}

void Window::DestroyResources()
{
    glfwTerminate();
}

void Window::ProcessInput()
{
    if (glfwGetKey(this->instance, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        this->Close();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(this->instance);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::Close()
{
    glfwSetWindowShouldClose(this->instance, true);
}

GLFWwindow* Window::GetInstance()
{
    return this->instance;
}

void Window::RecalculateSize()
{
    glfwGetWindowSize(this->instance, &this->width, &this->height);
    this->aspectRatio = (float)width / height;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
