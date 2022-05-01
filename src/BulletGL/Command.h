#include "Core.h"
#include "Model.h"
#include "Material.h"

class Command
{
public:
	void virtual Execute() = 0;
};

class DrawMeshCommand : public Command
{
public:	
	DrawMeshCommand(Model& vmesh, const glm::mat4& vmatrix, Material& vmaterial) :
		model(vmesh), matrix(vmatrix), material(vmaterial)
	{}

	~DrawMeshCommand() {}

	Model& model;
	const glm::mat4& matrix;
	Material& material;

	void Execute() override;
};