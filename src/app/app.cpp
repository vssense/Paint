#include "app.hpp"

//TODO:
// DONE 1) ADD absolute coordinates(or use it INSTEAD of relative ////////////// ADD OR REPLACE)
// 2) rewrite everything
// DONE 3) class GUIComponent - all methods are virtual, all windows should be inherited from it
// 4) think how to avoid non-linear inheritance - which methods should be in base classes
// 5) class App { PaintGUISystem*, Instuments }
// 6) subscribe to events
// 7) remove border from buttons, it should be another GUIComponent
// 8) implement on hover event. Should it be on timer? Or just every mouse motion

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

    GUIComponent* main_component = new GUIComponent(new Texture("img/pic.bmp"),
                                                    Rectangle{0, 0, kWindowWidth, kWindowHeight});

    main_component->Attach(new BasicButton(Rectangle{10,  10,  100, 30}, new ButtonCommand, kWhite, kRed, "button"));
    main_component->Attach(new Button     (Rectangle{200, 400, 100, 30}, new ButtonCommand, kRed, kWhite, kBlack, "xaxaxa", kLightPurple));

    PaintGUISystem system(&window, main_component);

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
