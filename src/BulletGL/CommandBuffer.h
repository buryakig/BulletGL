#include "Core.h"
#include "Model.h"
#include "Material.h"
#include "Command.h"



class CommandBuffer
{
public:

	CommandBuffer() : name("")
	{}

	~CommandBuffer();

	void DrawMesh(Model& mesh, glm::mat4& matrix, Material& material);
	void Execute();

	std::string name;
	std::vector<Command*> commands;
};
