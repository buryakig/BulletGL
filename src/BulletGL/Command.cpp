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
}