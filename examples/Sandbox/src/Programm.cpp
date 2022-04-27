
#include "Application.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "UI.h"
#include "Managers/SceneManager.h"

#include <easy/profiler.h>


Model *cube;
Camera* mainCamera;

Light* mainLight;

Shader* quadShader;
Shader* shadowmapShader;
UI* ui;

CommandBuffer* mainCmdBuffer;
SceneManager* sceneManager;

glm::mat4 cubeModel;


void Application::OnStart()
{

    sceneManager = new SceneManager();
    sceneManager->LoadScene("res/Scenes/Scene.yaml");

    mainCmdBuffer = new CommandBuffer();

    mainCamera = new Camera(this->window);
    mainCamera->SetUp();

    mainLight = new Light(glm::vec3(-3.0f, 3.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    mainLight->SetUp();

    ui = new UI(this->window);
    ui->SetUp();

    cube = new Model("res/Models/Cube/cube.obj");

    cubeModel = glm::mat4(1.0f);
    
    quadShader = new Shader("res/Shaders/solidColor.vert", "res/Shaders/tunableColor.frag");
    shadowmapShader = new Shader("res/Shaders/shadowMap.vert", "res/Shaders/shadowMap.frag");

    mainCmdBuffer->DrawMesh(*cube, cubeModel, *quadShader);

    mainCamera->AddCommandBuffer(mainCmdBuffer);
}

void Application::OnUpdate()
{
    glEnable(GL_DEPTH_TEST);
    mainCamera->Update();

    mainCamera->ExecuteCommandBuffers();

    ui->Draw();
}


void Application::OnDestroy()
{
    delete quadShader;
    delete shadowmapShader;
    delete mainLight;
    delete mainCamera;
    delete mainCmdBuffer;
    delete ui;
    delete cube;
    delete sceneManager;
}




int main()
{
	Application App;

	App.Init();
	
	App.Run();
}


