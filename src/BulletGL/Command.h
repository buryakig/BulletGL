#include "Core.h"
#include "Model.h"
#include "Material.h"

class Command
{
public:
	void virtual Execute() = 0;
};

class DrawModelCommand : public Command
{
public:	
	DrawModelCommand(Model& vmodel, const glm::mat4& vmatrix, Material* vmaterial) :
		model(vmodel), matrix(vmatrix), material(vmaterial)
	{}

	DrawModelCommand(Model& vmodel, const glm::mat4& vmatrix) :
		model(vmodel), matrix(vmatrix), material(nullptr)
	{}

	~DrawModelCommand() {}

	Model& model;
	const glm::mat4& matrix;
	Material* material;

	void Execute() override;
};