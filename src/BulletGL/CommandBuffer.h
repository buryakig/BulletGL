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

	void DrawModel(Model& model, glm::mat4& matrix, Material* material);
	void DrawModel(Model& model, glm::mat4& matrix);
	void Execute();

	std::string name;
	std::vector<Command*> commands;
};
