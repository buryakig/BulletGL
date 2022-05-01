#include "Command.h"

void DrawMeshCommand::Execute()
{
    //std::cout << "DrawMeshCommand executed" << std::endl;
    //std::cout << mesh.meshes[0]->vertices.size() << std::endl;

    material.SetMatrix("model", matrix);
    model.Draw(material);
}
