#pragma once

struct Vector3
{
public:
	Vector3(): x(0), y(0), z(0) {}
	Vector3(float valx, float valy, float valz): x(valx), y(valy), z(valz) {}

	float x, y, z;
};

