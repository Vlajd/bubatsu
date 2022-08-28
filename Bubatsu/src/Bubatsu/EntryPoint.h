#pragma once

#ifdef BBZ_PLATFORM_WINDOWS
	extern Bubatsu::Application* Bubatsu::CreateApplication();

	int main(int arc, char** argv)
	{
		Bubatsu::Log::Init();
		BBZ_CORE_WARN("INITED BUBAZ LOG!");

		auto app = Bubatsu::CreateApplication();
		app->Run();
		delete app;

		return 0;
	}
#endif

