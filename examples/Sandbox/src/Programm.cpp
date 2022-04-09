
#include "Application.h"
#include "Mesh.h"
#include "Camera.h"
#include "UI.h"



Mesh quad;
Camera* mainCamera;

Shader* quadShader;
UI* ui;

glm::mat4 quadModel;


void Application::OnStart()
{
    mainCamera = new Camera(this->window);
    mainCamera->SetUp();

    ui = new UI(this->window);
    ui->SetUp();

    quad.vertices = std::vector<glm::vec3>{
            glm::vec3(0.5f,  0.5f, -5.0f),  // top right
            glm::vec3(0.5f, -0.5f, -5.0f),  // bottom right
            glm::vec3(-0.5f, -0.5f,-5.0f),  // bottom left
            glm::vec3(-0.5f,  0.5f,-5.0f),   // top left
        };

    quad.indices = std::vector<unsigned int>{  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

    quadModel = glm::mat4(1.0f);
    quad.Prepare();
    
    quadShader = new Shader("res/Shaders/solidColor.vert", "res/Shaders/solidColor.frag");
}

void Application::OnUpdate()
{
    //mainCamera->Update();
        
    //mainCamera->DrawMesh(quad, quadModel, *quadShader);
    
    ui->Draw();
}


void Application::OnDestroy()
{
    delete quadShader;
    delete mainCamera;
    delete ui;
}




int main()
{
	Application App;

	App.Init();
	
	App.Run();
}


