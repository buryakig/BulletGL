#include "Transform.h"
#include "Model.h"
#include "Shader.h"

class Light
{
public:
	Light() : SHADOW_WIDTH(1024), SHADOW_HEIGHT(1024),
				nearPlane(1.0), farPlane(20.0),
				color(glm::vec4(1)), direction(glm::vec3(0.0, 1.0, 0.0)),
				transform() {};

	Light(glm::vec3 pos, glm::vec3 dir) : SHADOW_WIDTH(1024), SHADOW_HEIGHT(1024),
				nearPlane(1.0), farPlane(20.0),
				color(glm::vec4(1)), direction(dir),
				transform()
	{
		transform.position = pos;
	};

	~Light();

	Shader shadowmapShader;

	Transform transform;
	glm::vec3 direction;

	glm::vec4 color;

	glm::mat4 lightToWorldMatrix;
	glm::mat4 lightProjectionMatrix;

	unsigned int SHADOW_WIDTH, SHADOW_HEIGHT;
	float nearPlane, farPlane;

	unsigned int shadowMap;
	unsigned int shadowMapFBO;

	unsigned int lightUniformBuffer;

	void SetUp();
	void Update();
	void UpdateLightData();
	void CreateCameraDataBuffer();
	void DrawModel(Model& model, glm::mat4 matrix, const Shader& material);

private:
};