
#include "Application.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"
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
Shader* colorShader;

Material* quadMaterial;
Material* litMaterial;

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
    colorShader = new Shader("res/Shaders/colorShader.vert", "res/Shaders/colorShader.frag");
    shadowmapShader = new Shader("res/Shaders/shadowMap.vert", "res/Shaders/shadowMap.frag");

    quadMaterial = new Material(quadShader);
    quadMaterial->SetColor("fColor", glm::vec4(1.0, 0.0, 0.0, 1.0));

    litMaterial = new Material(colorShader);

    mainCmdBuffer->DrawMesh(*cube, cubeModel, *litMaterial);

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
    delete colorShader;
    delete quadMaterial;
    delete litMaterial;
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


