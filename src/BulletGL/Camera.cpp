#include "Camera.h"
#include "Model.h"
#include "UI.h"

namespace BulletGL
{
    float lastX = 1600.0f / 2.0;
    float lastY = 980.0 / 2.0;

    float yaw = 90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;

    bool firstMouse = true;

    void Camera::SetUp()
    {
        CreateCameraDataBuffer();
    }

    void Camera::Update()
    {
        ProcessMovement();

        cameraToWorldMatrix = glm::lookAt(transform->position, transform->position + transform->forward, transform->up);
        viewProjectionMatrix = glm::perspective(glm::radians(fov), 1600.0f / 980.0f, 0.1f, 1000.0f);

        UpdateCameraDataBuffer();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glViewport(0, 0, window->width, window->height);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Text("Camera pos. (%.1f, %.1f, %.1f)", transform->position.x,transform->position.y,transform->position.z);               // Display some text (you can use a format strings too)

        ImGui::End();
    }

    void Camera::CreateCameraDataBuffer()
    {
        int camBufferSize = sizeof(PerFrameCameraData);

        glCreateBuffers(1, &cameraUniformBuffer);
        glNamedBufferStorage(cameraUniformBuffer, camBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, cameraUniformBuffer);
    }

    void Camera::UpdateCameraDataBuffer()
    {
        int camBufferSize = sizeof(PerFrameCameraData);
        cameraData.mvp = viewProjectionMatrix * cameraToWorldMatrix;
        cameraData.cameraPos = transform->position;

        glNamedBufferSubData(cameraUniformBuffer, 0, camBufferSize, &cameraData);
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
            transform->position += transform->forward;
        if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
            transform->position -= transform->forward;
        if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
            transform->position -= glm::normalize(glm::cross(transform->forward, transform->up));
        if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
            transform->position += glm::normalize(glm::cross(transform->forward, transform->up));
    }

    void Camera::BindFrameBuffer(RenderTexture* rTex)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, rTex->FBO);
    }

    void Camera::BindFrameBuffer(unsigned bufferID)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
    }

    void Camera::AddCommandBuffer(CommandBuffer* cb)
    {
        cmdBuffers.push_back(cb);
    }

    void Camera::ExecuteCommandBuffers()
    {
        for (CommandBuffer* cmdbuff : cmdBuffers)
        {
            cmdbuff->Execute();
        }
    }

}