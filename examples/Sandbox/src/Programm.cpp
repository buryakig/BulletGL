
#include "Application.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "UI.h"

#include <easy/profiler.h>


Model *cube;
Camera* mainCamera;

Light* mainLight;

Shader* quadShader;
Shader* shadowmapShader;
UI* ui;

glm::mat4 cubeModel;


void Application::OnStart()
{

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
}

void Application::OnUpdate()
{
    // Start Light routine
    mainLight->Update();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    shadowmapShader->use();
    cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
    mainLight->DrawModel(*cube, cubeModel, *shadowmapShader);

    cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(3.0, 0.0, 0.0));
    mainLight->DrawModel(*cube, cubeModel, *shadowmapShader);

    cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(3.0, 0.0, -3.0));
    mainLight->DrawModel(*cube, cubeModel, *shadowmapShader);

    cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 2.0, -3.0));
    mainLight->DrawModel(*cube, cubeModel, *shadowmapShader);

    cubeModel = glm::scale(glm::mat4(1.0f), glm::vec3(10, 0.01, 10));
    cubeModel = glm::translate(cubeModel, glm::vec3(0.0, -50.1, 0.0));
    mainLight->DrawModel(*cube, cubeModel, *shadowmapShader);

    ImGui::Begin("Shadowmap");
    ImGui::Text("Cam pos: %.2f %.2f %.2f ", mainCamera->transform->position.x,mainCamera->transform->position.y,mainCamera->transform->position.z);
    ImGui::Image((void*)(intptr_t)mainLight->shadowMap, ImVec2(512, 512), ImVec2(0,1),ImVec2(1, 0));
    ImGui::End();
    glCullFace(GL_BACK);


    // Start Camera routine
    mainCamera->Update();
    quadShader->use();
    quadShader->setInt("shadowMap", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mainLight->shadowMap);
    cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
    quadShader->setVector("fColor", 0.7, 0.0, 0.0, 1.0);
    mainCamera->DrawModel(*cube, cubeModel, *quadShader);

    cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(3.0, 0.0, 0.0));
    quadShader->setVector("fColor", 0.7, 0.7, 0.0, 1.0);
    mainCamera->DrawModel(*cube, cubeModel, *quadShader);

    cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(3.0, 0.0, -3.0));
    quadShader->setVector("fColor", 0.0, 0.7, 0.0, 1.0);
    mainCamera->DrawModel(*cube, cubeModel, *quadShader);

    cubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 2.0, -3.0));
    quadShader->setVector("fColor", 0.4, 0.2, 0.7, 1.0);
    mainCamera->DrawModel(*cube, cubeModel, *quadShader);

    cubeModel = glm::scale(glm::mat4(1.0f), glm::vec3(10, 0.01, 10));
    cubeModel = glm::translate(cubeModel, glm::vec3(0.0, -50.1, 0.0));
    quadShader->setVector("fColor", 0.7, 0.7, 0.75, 1.0);
    mainCamera->DrawModel(*cube, cubeModel, *quadShader);
    
    glDisable(GL_DEPTH_TEST);

    ui->Draw();
}


void Application::OnDestroy()
{
    delete quadShader;
    delete shadowmapShader;
    delete mainLight;
    delete mainCamera;
    delete ui;
    delete cube;
}




int main()
{
	Application App;

	App.Init();
	
	App.Run();


    profiler::dumpBlocksToFile("profiler_dump.prof"); 
    
}


