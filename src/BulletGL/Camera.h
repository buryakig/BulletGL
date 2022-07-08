#pragma once
#include "CommandBuffer.h"
#include "RenderTexture.h"
#include "Transform.h"
#include "Model.h"
#include "Window.h"
#include "Shader.h"


namespace BulletGL
{

	struct PerFrameCameraData {
		glm::mat4 mvp{ 0.0 };
		glm::vec3 cameraPos{ 0.0 };
	};

	class Camera
	{
	public:


		Camera(Window* w) 
			: cameraData{}
			, fov{60}
			, cameraToWorldMatrix{ 0.0 }
			, viewProjectionMatrix{ 0.0 }
			, window{ w }
			, transform{ new Transform() }
			, cameraUniformBuffer{0}
		{
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

		void BindFrameBuffer(RenderTexture* rTex);
		void BindFrameBuffer(unsigned bufferID);

		void AddCommandBuffer(CommandBuffer* cb);
		void ExecuteCommandBuffers();

	private:
		unsigned int cameraUniformBuffer;

		PerFrameCameraData cameraData;

		std::vector<CommandBuffer*> cmdBuffers;
	};
}