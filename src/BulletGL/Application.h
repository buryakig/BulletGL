#pragma once
#include "Window.h"

namespace BulletGL
{
	class Application
	{
	public:

		Application();
		~Application();

		void Init();
		int Run();

		void OnUpdate();
		void OnStart();
		void OnDestroy();

		Window* window;
	};

}