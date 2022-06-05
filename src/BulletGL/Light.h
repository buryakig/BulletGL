#pragma once

#include <array>

#include "Transform.h"
#include "Model.h"
#include "Shader.h"

namespace BulletGL
{
	class Light
	{
	public:
		Light() : SHADOW_WIDTH(1024), SHADOW_HEIGHT(1024),
			nearPlane(1.0), farPlane(100.0),
			color(glm::vec4(1)),
			transform() {};

		Light(glm::vec3 pos, glm::vec3 rotation) : SHADOW_WIDTH(1024), SHADOW_HEIGHT(1024),
			nearPlane(1.0), farPlane(20.0),
			color(glm::vec4(1)),
			transform()
		{
			transform.position = pos;
			transform.rotation = rotation;
		};

		~Light();

		Shader shadowmapShader;

		Transform transform;

		glm::vec4 color;

		glm::mat4 lightToWorldMatrix;
		glm::mat4 lightProjectionMatrix;

		float intensity;

		unsigned int SHADOW_WIDTH, SHADOW_HEIGHT;
		float nearPlane, farPlane;

		unsigned int shadowMap;
		unsigned int shadowMapFBO;


		void SetUp();
		void Update();

		void UpdateLightData();
		void CreateCameraDataBuffer();

		static unsigned int lightUniformBuffer;

		static std::array<Light*, 8> dirLights;

	private:
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight() { addLight(); };
		~DirectionalLight();

		void addLight();

		glm::vec3 direction = glm::vec3(0.0, -1.0, 0.0);

	};
}