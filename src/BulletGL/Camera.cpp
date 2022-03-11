#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, 
    float fieldOfView, float nearPlane, float farPlane ) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Yaw(YAW), Pitch(PITCH)
{
    Position = position;
    WorldUp = up;
    FieldOfView = fieldOfView;
    NearPlane = nearPlane;
    FarPlane = farPlane;

    UpdateVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspect)
{
	return glm::perspective(glm::radians(FieldOfView), aspect, NearPlane, FarPlane);
}

void Camera::ProcessMovement(Enum::CameraMovement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
    if (direction == Enum::FORWARD)
        Position += Front * velocity;
    if (direction == Enum::BACKWARD)
        Position -= Front * velocity;
    if (direction == Enum::LEFT)
        Position -= Right * velocity;
    if (direction == Enum::RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;
    

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateVectors();
}

void Camera::UpdateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}