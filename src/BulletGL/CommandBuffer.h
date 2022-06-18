#include "Core.h"
#include "Model.h"
#include "Material.h"
#include "Command.h"



namespace BulletGL
{
	class CommandBuffer
	{
	public:

		CommandBuffer() : name("")
		{}

		~CommandBuffer();

		void DrawModel(Model& model, glm::mat4& matrix, Material* material);
		void DrawModel(Model& model, glm::mat4& matrix);
		void SetRenderTaget(RenderTexture* rT);
		void Blit(Texture* src, RenderTexture* dest = nullptr, Material* mat = nullptr);
		void Swap(Texture* t1, Texture* t2);

		void Execute();

		std::string name;
		std::vector<Command*> commands;
	};
}