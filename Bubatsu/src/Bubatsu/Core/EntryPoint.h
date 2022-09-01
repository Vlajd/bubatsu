#pragma once

#ifdef BBZ_PLATFORM_WINDOWS
    extern Bubatsu::Application* Bubatsu::BubatsuMain();

    int main(int arc, char** argv)
    {
        Bubatsu::Log::Init();
        BBZ_CORE_WARN("INITED BUBAZ LOG!");

        auto app = Bubatsu::BubatsuMain();
        app->Run();
        delete app;

        return 0;
    }
#endif

