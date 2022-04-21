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
	DrawMeshCommand* cmd = new DrawMeshCommand(mesh, matrix, material);
	//Command* cmd = new Command();

	commands.push_back(cmd);
}

void CommandBuffer::Execute()
{
	for (Command* cmd : commands)
	{
		cmd->Execute();
	}
}
