#include "CommandBuffer.h"

CommandBuffer::~CommandBuffer()
{
	for (Command* cmd : commands)
	{
		delete cmd;
	}
}

void CommandBuffer::DrawMesh(Model& mesh, glm::mat4& matrix, Shader& material)
{
	commands.push_back(new DrawMeshCommand(mesh, matrix, material));
}

void CommandBuffer::Execute()
{
	for (Command* cmd : commands)
	{
		cmd->Execute();
	}
}
