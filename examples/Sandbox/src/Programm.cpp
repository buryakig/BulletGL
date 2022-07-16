
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
    Model* sponzaModel;
    Model* sphereModel;
    Model* cubeModel;
    Camera* mainCamera;

    Light* mainLight;

    Shader* shadowmapShader;
    Shader* defaultShader;
    Shader* emptyShader;
    Shader* screenShader;
    Shader* extractBlurShader;
    Shader* horizontalBlurShader;
    Shader* verticalBlurShader;

    Material* quadMaterial;
    Material* extractBlurMaterial;
    Material* hblurMaterial;
    Material* vblurMaterial;

    RenderTexture* renderTex;
    RenderTexture* test_delete_me;
    RenderTexture* extractedBlur;
    RenderTexture* blur1;
    RenderTexture* blur2;

    Texture* envMap;

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
        renderTex = new RenderTexture(window->width, window->height, 1, GL_RGBA16F, true);
        extractedBlur = new RenderTexture(window->width, window->height, 1, GL_RGBA16F, true);
        blur1 = new RenderTexture(window->width, window->height, 1, GL_RGBA16F, true);
        blur2 = new RenderTexture(window->width, window->height, 1, GL_RGBA16F, true);

        // Matrices
        sponzaLocalMatrix = glm::mat4(1.0f);
        //sponzaLocalMatrix = glm::scale(sponzaLocalMatrix, glm::vec3(0.1, 0.1, 0.1));

        // Shaders
        Shader::SetUp();
        shadowmapShader = Resources::LoadShader("res/Shaders/shadowMap.vert", "res/Shaders/shadowMap.frag");
        screenShader = Resources::LoadShader("res/Shaders/blitShader.vert", "res/Shaders/screenShader.frag");
        extractBlurShader = Resources::LoadShader("res/Shaders/blitShader.vert", "res/Shaders/extractBlur.frag");
        horizontalBlurShader = Resources::LoadShader("res/Shaders/blitShader.vert", "res/Shaders/horizontalBlur.frag");
        verticalBlurShader = Resources::LoadShader("res/Shaders/blitShader.vert", "res/Shaders/verticalBlur.frag");

        // Textures

        // Materials
        Material::SetUp();

        quadMaterial = new Material(screenShader);
        quadMaterial->SetTexture("_BloomTex", blur1);

        extractBlurMaterial = new Material(extractBlurShader);
        hblurMaterial = new Material(horizontalBlurShader);
        vblurMaterial = new Material(verticalBlurShader);


        // Models
        //sponzaModel = Resources::LoadModel("res/Models/teapot_pbr/uploads_files_3449455_teapotf.obj");
        sphereModel = Resources::LoadModel("res/Models/Sphere/3d-model.obj");

        cubeModel = Resources::LoadModel("res/Models/Cube/cube.obj");

        // CommandBuffer routine
        mainCmdBuffer->SetRenderTaget(renderTex);
        mainCmdBuffer->DrawModel(*sphereModel, sponzaLocalMatrix);

        //mainCmdBuffer->Blit(renderTex, extractedBlur, extractBlurMaterial);
        //mainCmdBuffer->Blit(extractedBlur, blur1, hblurMaterial);
        //
        //for (int i = 0; i < 10; ++i)
        //{
        //    mainCmdBuffer->Blit(blur1, blur2, hblurMaterial);
        //    mainCmdBuffer->Blit(blur2, blur1, vblurMaterial);
        //}

        mainCmdBuffer->Blit(renderTex, nullptr, quadMaterial);

        mainCamera->AddCommandBuffer(mainCmdBuffer);
    }

    void Application::OnUpdate()
    {
        mainCamera->Update();
        mainCamera->ExecuteCommandBuffers();
        

        //ImGui::Begin("OpenGL Texture Text");
        //ImGui::Text("pointer = %p", blur1->id);
        //ImGui::Text("size = %d x %d", 1024, 1024);
        //ImGui::Image((void*)(intptr_t)blur1->id, ImVec2(1024, 1024));
        //ImGui::End();

        ui->Draw();
    }


    void Application::OnDestroy()
    {
        delete mainLight;
        delete mainCamera;
        delete mainCmdBuffer;
        delete ui;
        delete renderTex;
        delete extractedBlur;

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