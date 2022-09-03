#define BBZ_ENTRY_POINT
#include <Bubatsu.h>
#include "ExampleLayer.h"
#include "ExampleRenderer2D.h"

class Sandbox : public Bubatsu::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleRenderer2D());
    }

    ~Sandbox() {}
};

Bubatsu::Application* Bubatsu::BubatsuMain()
{
    return new Sandbox();
}

