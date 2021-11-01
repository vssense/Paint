#include "app.hpp"

void App::operator () ()
{

    Window window{};
    Renderer renderer(&window);
    bool is_running = true;

    GUIComponentSystem system(&window, CreatePaintTree(&renderer, &is_running, &system));

    while (is_running)
    {
        Event event;
        while (event.PollEvent() && is_running)
        {
            switch (event.GetType())
            {
                case kQuit:
                {
                    is_running = false;
                    break;
                } 
                case kKeyDown:
                {
                    printf("scancode %d\n", event.GetValue().scancode);
                    if (event.GetValue().scancode == kQScancode)
                    {
                        is_running = false;
                    }

                    break;
                }
                case kMouseButtonPress:
                case kMouseButtonRelease:
                case kMouseButtonOldRelease:
                case kMouseMotion:
                {
                    system.ProcessEvent(event);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        renderer.Clear();

        system.Render(&renderer);

        renderer.Present();
    }
}
