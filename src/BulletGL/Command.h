#include "Core.h"
#include "Model.h"
#include "Shader.h"

class Command
{
public:
	void virtual Execute() = 0;
};

class DrawMeshCommand : public Command
{
public:	
	DrawMeshCommand(Model& vmesh, glm::mat4& vmatrix, Shader& vmaterial) :
		mesh(vmesh), matrix(vmatrix), material(vmaterial)
	{}

	~DrawMeshCommand() {}

	Model mesh;
	glm::mat4 matrix;
	Shader material;

	void Execute() override;
};