#pragma once

#ifdef BBZ_PLATFORM_WINDOWS
    extern Bubatsu::Application* Bubatsu::BubatsuMain();

    int main(int arc, char** argv)
    {
        Bubatsu::Log::Init();

        BBZ_PROFILE_BEGIN_SESSION("Startup", "Debug/BubatsuProfile-Startup.json");
        auto app = Bubatsu::BubatsuMain();
        BBZ_PROFILE_END_SESSION();

        BBZ_PROFILE_BEGIN_SESSION("Runtime", "Debug/BubatsuProfile-Runtime.json");
        app->Run();
        BBZ_PROFILE_END_SESSION();

        BBZ_PROFILE_BEGIN_SESSION("Shutdown", "Debug/BubatsuProfile-Shutdown.json");
        delete app;
        BBZ_PROFILE_END_SESSION();

        return 0;
    }
#endif

