#pragma once
#include "Window.h"
#include "Shader.h"
#include <imgui/imgui.h>

namespace BulletGL
{
	class UI
	{
	public:
		UI(Window* wnd) : window(wnd) { };

		~UI();

		void SetUp();
		void Draw();

	private:

		Window* window;

		const char* glsl_version = "#version 460";
	};
}