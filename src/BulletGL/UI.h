#pragma once
#include "Window.h"
#include "Shader.h"
#include <imgui/imgui.h>

class UI
{
public:
	UI(Window* wnd) : window(wnd), 
		VBO(0), EBO(0), VAO(0), 
		perFrameDataBuffer(0) { };

	~UI();

	void SetUp();
	void Draw();

private:

	Shader* uiShader;
	Window* window;

	unsigned int VBO, EBO, VAO;
	unsigned int perFrameDataBuffer;


	static const GLchar const* shaderPathVertex;
	static const GLchar const* shaderPathFragment;
};
