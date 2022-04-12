#include "Application.h"
#include "UI.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

GLFWwindow* window;

Application::Application()
{
    window = new Window();
}

Application::~Application()
{
    OnDestroy();

    window->DestroyResources();
    delete window;
}

void Application::Init()
{
    window->Initialize();
    window->Create("Main Window", 1600, 980);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    OnStart();
}

int Application::Run()
{   
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!window->ShouldClose())
    {
        window->RecalculateSize();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        OnUpdate();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window->SwapBuffers();
        window->PollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    return 0;
}
