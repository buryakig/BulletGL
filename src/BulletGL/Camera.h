#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Enum
{
	enum CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
}
// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.2f;
const float ZOOM = 60.0f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000.0f;

class Camera
{
public:
	// camera attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler angels
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float FieldOfView;
	float NearPlane;
	float FarPlane;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float fieldOfView = ZOOM, float nearPlane = NEAR_PLANE, float farPlane = FAR_PLANE);
	
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float aspect);

	void ProcessMovement(Enum::CameraMovement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yofset);

private:
	void UpdateVectors();
};

