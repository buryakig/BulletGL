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

	void CommandBuffer::SetRenderTaget(RenderTexture* rT)
	{
		commands.push_back(new SetRenderTargetCommand(rT));
	}

	void CommandBuffer::Blit(Texture* src, RenderTexture* dest, Material* mat)
	{
		commands.push_back(new BlitCommand(src, dest, mat));
	}

	void CommandBuffer::Swap(Texture* t1, Texture* t2)
	{
		commands.push_back(new SwapCommand(t1, t2));
	}

	void CommandBuffer::Execute()
	{
		for (Command* cmd : commands)
		{
			cmd->Execute();
		}
	}
}