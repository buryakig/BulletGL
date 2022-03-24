#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "Window.h"
#include "Shader.h"



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

	void DrawMesh(Mesh& mesh, glm::mat4 matrix, const Shader& material);

private:
	unsigned int cameraUniformBuffer;

	PerFrameCameraData cameraData;

};