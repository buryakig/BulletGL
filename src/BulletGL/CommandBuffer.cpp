#include "CommandBuffer.h"

namespace BulletGL
{
	CommandBuffer::~CommandBuffer()
	{
		for (Command* cmd : commands)
		{
			delete cmd;
		}
	}

	//void CommandBuffer::DrawModel(Model& model, glm::mat4& matrix)
	//{
	//	commands.push_back(new DrawModelCommand(model, matrix, material));
	//}

	void CommandBuffer::DrawModel(Model& model, glm::mat4& matrix, Material* material)
	{
		commands.push_back(new DrawModelCommand(model, matrix, material));
	}

	void CommandBuffer::DrawModel(Model& model, glm::mat4& matrix)
	{
		commands.push_back(new DrawModelCommand(model, matrix));
	}

	void CommandBuffer::Execute()
	{
		for (Command* cmd : commands)
		{
			cmd->Execute();
		}
	}
}