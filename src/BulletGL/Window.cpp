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
    glfwSetErrorCallback([](int error, const char* desc) {std::cerr << "Error: " << desc << std::endl; });
    if (!glfwInit())
        exit(EXIT_FAILURE);
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
    glfwSetKeyCallback(this->instance,
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                glfwWindowShouldClose(window);
            }
        });
    return true;
}

void Window::SetCurrent()
{
    glfwMakeContextCurrent(this->instance);
    glfwSwapInterval(1);
}

void Window::DestroyResources()
{
    glfwDestroyWindow(this->instance);
    glfwTerminate(); 
}

void Window::ProcessInput()
{

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
