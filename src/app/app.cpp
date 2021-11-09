#include "app.hpp"

void App::operator () ()
{

    Window window{};
    Renderer::Construct(&window);
    Renderer* renderer = Renderer::GetInstance();

    bool is_running = true;

    PaintGUISystem system(&window, CreatePaintTree(&is_running, &system));

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
                    if (event.GetValue().scancode == kQScancode)
                    {
                        is_running = false;
                    }
                    else if (event.GetValue().scancode == kMinusScancode)
                    {
                        system.GetBrush().GetThickness()--;
                    }
                    else if (event.GetValue().scancode == kPlusScancode)
                    {
                        system.GetBrush().GetThickness()++;
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

        renderer->SetRenderTarget(nullptr);

        renderer->Clear();
        system.Render();
        renderer->Present();
    }
}
