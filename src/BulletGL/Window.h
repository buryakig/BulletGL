#pragma once

#include "Core.h"

class Window
{
public:

	int width, height;
	bool observerViewMode;
	float aspectRatio;

	Window();

	void Initialize();
	void SetCurrent();
	//void DestroyResources();
	void ProcessInput();
	void SwapBuffers();
	void Close();
	void RecalculateSize();
	//void PollEvents();

	bool ShouldClose();
	bool Create(const std::string& name, const int& width, const int& height);

	GLFWwindow* GetInstance();

private:
	GLFWwindow* instance;
};

void FramebufferResizeCallback(GLFWwindow* window, int width, int height);
