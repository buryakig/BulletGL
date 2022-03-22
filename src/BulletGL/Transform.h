#pragma once
#include "Core.h"

class Transform
{
public:

	Transform() :
		position(0),
		rotation(0),
		scale(1),
		forward(0, 0, 1),
		up(0, 1, 0),
		right(1, 0, 0)
	{}

	~Transform()
	{}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;

};

