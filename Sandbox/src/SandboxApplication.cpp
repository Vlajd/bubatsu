#define BBZ_ENTRY_POINT
#include <Bubatsu.h>
#include "ExampleLayer.h"

class Sandbox : public Bubatsu::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {}
};

Bubatsu::Application* Bubatsu::BubatsuMain()
{
    return new Sandbox();
}

