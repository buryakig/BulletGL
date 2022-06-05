#pragma once
#include "CommandBuffer.h"
#include "Transform.h"
#include "Model.h"
#include "Window.h"
#include "Shader.h"


namespace BulletGL
{

	struct PerFrameCameraData {
		glm::mat4 mvp;
		glm::vec3 cameraPos;
	};

	class Camera
	{
	public:


		Camera(Window* w) : fov(60)
		{
			window = w;
			transform = new Transform();
			transform->position = glm::vec3(0.0, 0.0, -10.0);
		}

		~Camera()
		{
			delete transform;
		}

		Window* window;
		Transform* transform;

		glm::mat4 cameraToWorldMatrix;
		glm::mat4 viewProjectionMatrix;



		float fov;

		void SetUp();
		void Update();

		void CreateCameraDataBuffer();
		void UpdateCameraDataBuffer();

		void ProcessMovement();

		void AddCommandBuffer(CommandBuffer* cb);
		void ExecuteCommandBuffers();

	private:
		unsigned int cameraUniformBuffer;

		PerFrameCameraData cameraData;

		std::vector<CommandBuffer*> cmdBuffers;
	};
}