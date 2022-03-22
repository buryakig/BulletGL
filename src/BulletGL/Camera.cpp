#include "Camera.h"

float lastX = 1600.0f / 2.0;
float lastY = 980.0 / 2.0;

float yaw = 90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;

bool firstMouse = true;

void Camera::Update()
{
    ProcessMovement();

    cameraToWorldMatrix = glm::lookAt(transform->position, transform->position + transform->forward, transform->up);
    viewProjectionMatrix = glm::perspective(glm::radians(fov), 1600.0f / 980.0f, 0.1f, 100.0f);
}

void Camera::ProcessMovement()
{
    GLFWwindow* glfwWindow = this->window->GetInstance();

    int state = glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT);


    double xpos, ypos;
    glfwGetCursorPos(glfwWindow, &xpos, &ypos);


        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }


        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;


    if (state == GLFW_PRESS)
    {
        float sensitivity = 0.2f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        transform->forward = glm::normalize(front);
    }

    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);

    //float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        transform->position += transform->forward * 0.1f;
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        transform->position -= transform->forward * 0.1f;
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        transform->position -= glm::normalize(glm::cross(transform->forward, transform->up)) * 0.1f;
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        transform->position += glm::normalize(glm::cross(transform->forward, transform->up)) * 0.1f;
}

void Camera::DrawMesh(Mesh& mesh, glm::mat4 matrix, const Shader& material)
{
    material.use();
    glm::mat4 MVP = viewProjectionMatrix * cameraToWorldMatrix * matrix ;
    material.setMatrix("_MVP", MVP);
    mesh.Draw();
}

