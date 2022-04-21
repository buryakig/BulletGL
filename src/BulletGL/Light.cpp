#include "Light.h"

Light::~Light()
{
}

void Light::SetUp()
{
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glGenFramebuffers(1, &shadowMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	CreateCameraDataBuffer();
}

void Light::CreateCameraDataBuffer()
{
	int lightBufferSize = sizeof(glm::mat4);

	glCreateBuffers(1, &lightUniformBuffer);
	glNamedBufferStorage(lightUniformBuffer, lightBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightUniformBuffer);
}

void Light::UpdateLightData()
{
	lightProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
	lightToWorldMatrix = glm::lookAt(glm::vec3(-3.0f, 3.5f, -3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 lightSpaceMatrix = lightProjectionMatrix * lightToWorldMatrix;

	int lightBufferSize = sizeof(glm::mat4);
	glNamedBufferSubData(lightUniformBuffer, 0, lightBufferSize, &lightSpaceMatrix);
}

void Light::Update()
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	UpdateLightData();
}

void Light::DrawModel(Model& model, glm::mat4 matrix, const Shader& material)
{
	material.setMatrix("model", matrix);
	model.Draw(material);
}
