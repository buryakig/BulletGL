#include "Command.h"

namespace BulletGL
{
    void DrawModelCommand::Execute()
    {
        //std::cout << "DrawMeshCommand executed" << std::endl;
        //std::cout << mesh.meshes[0]->vertices.size() << std::endl;
        if (material)
        {
            model.Draw(material, matrix);
        }
        else
        {
            model.Draw(matrix);
        }
    }


    void SetRenderTargetCommand::Execute()
    {
        if(renderTarget)
            glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->FBO);
        else
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    static Material* defaultMat = nullptr;
    void BlitCommand::Execute()
    {
        if (material)
        {
            material->SetTexture("_MainTex", source);
            material->Use();
        }

        if (destination)
            glBindFramebuffer(GL_FRAMEBUFFER, destination->FBO);
        else
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void SwapCommand::Execute()
    {
        Texture* tmp = firstTex;
        firstTex = secondTex;
        secondTex = firstTex;
    }

}