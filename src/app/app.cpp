#include "app.hpp"

//TODO:
// DONE 1) ADD absolute coordinates(or use it INSTEAD of relative ////////////// ADD OR REPLACE)
// DONE 3) class GUIComponent - all methods are virtual, all windows should be inherited from it
// 5) class App { PaintGUISystem*, Instuments }
// DONE 6) subscribe to events
// 7) remove border from buttons, it should be another GUIComponent
// DONE 8) implement on hover event. Should it be on timer? Or just every mouse motion
// 9) Event Manager - singleton - main window close pushes kQuit event  

class ButtonCommand : public ICommand
{
    virtual void Execute() override
    {
        printf("Click\n");
    }
};

void App::operator () ()
{
    Window window{};
    Renderer::Construct(&window);
    Renderer* renderer = Renderer::GetInstance();

    bool is_running = true;

    PaintGUISystem system(&window, new PaintMainComponent(new Texture("img/pic.bmp")));

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
                } break;
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
                } break;
                default:
                {
                    system.ProcessEvent(event);
                } break;
            }
        }

        renderer->SetRenderTarget(nullptr);

        renderer->Clear();
        system.Render();
        renderer->Present();
    }
}
