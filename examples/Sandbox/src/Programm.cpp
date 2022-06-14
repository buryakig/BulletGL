
#include "Application.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"
#include "RenderTexture.h"
#include "Camera.h"
#include "Light.h"
#include "UI.h"
#include "Utils/Resources/Resources.h"

#include <easy/profiler.h>


namespace BulletGL
{
    Model* cube;
    Camera* mainCamera;

    Light* mainLight;

    Shader* shadowmapShader;
    Shader* defaultShader;
    Shader* emptyShader;
    Shader* screenShader;

    Material* quadMaterial;
    Material* litMaterial;

    RenderTexture* renderTex;
    RenderTexture* test_delete_me;

    UI* ui;

    CommandBuffer* mainCmdBuffer;

    glm::mat4 sponzaLocalMatrix;


    void Application::OnStart()
    {
        mainCmdBuffer = new CommandBuffer();

        mainCamera = new Camera(this->window);
        mainCamera->SetUp();

        mainLight = new Light(glm::vec3(-3.0f, 3.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        mainLight->SetUp();

        ui = new UI(this->window);
        ui->SetUp();

        // Render Textures
        renderTex = new RenderTexture(window->width, window->height, GL_RGBA, GL_RGBA16F, true);

        // Matrices
        sponzaLocalMatrix = glm::mat4(1.0f);
        sponzaLocalMatrix = glm::scale(sponzaLocalMatrix, glm::vec3(0.1, 0.1, 0.1));

        // Shaders
        Shader::SetUp();
        shadowmapShader = Resources::LoadShader("res/Shaders/shadowMap.vert", "res/Shaders/shadowMap.frag");
        screenShader = Resources::LoadShader("res/Shaders/screenShader.vert", "res/Shaders/screenShader.frag");

        // Materials
        Material::SetUp();

        // Models
        cube = Resources::LoadModel("res/Models/sponza/sponza.obj");

        mainCmdBuffer->DrawModel(*cube, sponzaLocalMatrix);

        mainCamera->AddCommandBuffer(mainCmdBuffer);
    }

    void Application::OnUpdate()
    {
        mainCamera->Update();

        Texture* texture = Resources::textures[0];

        mainCamera->BindFrameBuffer(renderTex);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mainCamera->ExecuteCommandBuffers();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
        screenShader->use();
        glUniform1i(glGetUniformLocation(screenShader->programID, "screenTex"),
                        0);
        glBindTextureUnit(0, renderTex->id);

        glDrawArrays(GL_TRIANGLES, 0, 6);



        ui->Draw();
    }


    void Application::OnDestroy()
    {
        delete mainLight;
        delete mainCamera;
        delete mainCmdBuffer;
        delete ui;

        Resources::DeallocateMemory();
        Material::DeallocateMemory();
    }




}


int main()
{
    BulletGL::Application App;

    App.Init();

    App.Run();
}