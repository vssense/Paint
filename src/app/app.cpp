#include "app.hpp"

//TODO:
// Add border as a field to GUIComponent? Also make it more beautiful
// WHO DELETE SINGLETONS BLYAT

void App::Run()
{
    Window window{};
    Renderer::Construct(&window);
    Renderer* renderer = Renderer::GetInstance();

    bool is_running = true;
    PaintGUISystem system(&window, new PaintMainComponent(new Texture("img/pic.bmp")));

    while (is_running)
    {
        // clock_t t = clock();

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
                    break;
                }
                default:
                {
                    system.ProcessEvent(event);
                    break;
                }
            }
        }

        renderer->SetRenderTarget(nullptr);

        renderer->Clear();
        system.Render();
        renderer->Present();
    }

    Renderer::Destruct();
    PluginManager::Destruct();
    // Manager<ITool*>::Destruct();
    // Manager<IFilter*>::Destruct();
}
