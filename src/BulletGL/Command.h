#include "Core.h"
#include "Model.h"
#include "RenderTexture.h"
#include "Material.h"

namespace BulletGL
{
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

	class SetRenderTargetCommand : public Command
	{
	public:
		SetRenderTargetCommand() :
			renderTarget(nullptr)    	{}
		SetRenderTargetCommand(RenderTexture* rT) :
			renderTarget(rT)    	{}
		~SetRenderTargetCommand()	{}

		RenderTexture* renderTarget;

		void Execute() override;
	};

	class BlitCommand : public Command
	{
	public:
		BlitCommand(Texture* src, RenderTexture* dest = nullptr, Material* mat = nullptr)
			: source(src), destination(dest), material(mat){}
		~BlitCommand()	{}

		Texture* source;
		RenderTexture* destination;
		Material* material;

		static  Material const * const defaultMat;

		void Execute() override;
	};

	class SwapCommand : public Command
	{
	public:
		SwapCommand(Texture*& t1, Texture*& t2)
			: firstTex(t1), secondTex(t2){}
		~SwapCommand()	{}

		Texture*& firstTex;
		Texture*& secondTex;

		static  Material const * const defaultMat;

		void Execute() override;
	};

}