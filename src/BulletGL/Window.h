#pragma once

#include "Core.h"

class Window
{
public:

	int width, height;
	bool observerViewMode;
	float aspectRatio;

	Window();
	Window(int w, int h);

	void Initialize();
	void SetCurrent();
	void DestroyResources();
	void ProcessInput();
	void SwapBuffers();
	void PollEvents();
	void Close();
	void RecalculateSize();

	bool ShouldClose();
	bool Create(const std::string& name, const int& width, const int& height);

	GLFWwindow* GetInstance();

private:
	GLFWwindow* instance;
};

void FramebufferResizeCallback(GLFWwindow* window, int width, int height);
