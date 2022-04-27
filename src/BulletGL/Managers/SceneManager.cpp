#include "SceneManager.h"
#include "../Utils/TextReader.h"

void SceneManager::LoadScene(const std::string& scenePath)
{
	YAML::Node config = YAML::LoadFile(scenePath);
}
