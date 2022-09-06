#pragma once

#ifdef BBZ_PLATFORM_WINDOWS
    extern Bubatsu::Application* Bubatsu::BubatsuMain();

    int main(int arc, char** argv)
    {
        Bubatsu::Log::Init();

        BBZ_PROFILE_BEGIN_SESSION("Startup", "Debug/BubatsuProfile-Startup.dbg.json");
        auto app = Bubatsu::BubatsuMain();
        BBZ_PROFILE_END_SESSION();

        BBZ_PROFILE_BEGIN_SESSION("Runtime", "Debug/BubatsuProfile-Runtime.dbg.json");
        app->Run();
        BBZ_PROFILE_END_SESSION();

        BBZ_PROFILE_BEGIN_SESSION("Shutdown", "Debug/BubatsuProfile-Shutdown.dbg.json");
        delete app;
        BBZ_PROFILE_END_SESSION();

        return 0;
    }
#endif

