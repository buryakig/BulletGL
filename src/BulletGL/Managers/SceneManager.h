#pragma once
#include <string>

#include "../Camera.h"
#include "../Light.h"

class SceneManager
{
public:
	SceneManager() : mainCamera(nullptr), mainLight(nullptr)
	{}
	~SceneManager() {}
	
	void LoadScene(const std::string& scenePath);

	Camera* mainCamera;
	Light* mainLight;
};
