#include "Core.h"
#include "Model.h"
#include "Shader.h"
#include "Command.h"



class CommandBuffer
{
public:

	CommandBuffer() : name("")
	{}

	~CommandBuffer();

	void DrawMesh(Model& mesh, glm::mat4& matrix, Shader& material);
	void Execute();

	std::string name;
	std::vector<Command*> commands;
};
