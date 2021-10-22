#include "app.hpp"

void App::operator () ()
{
    Window window{};
    Renderer renderer(&window);

    bool is_running = true;

    while (is_running)
    {
        Event event;
        while (event.PollEvent())
        {
            if ((event.GetType() == Quit) || (event.GetType() == KeyDown && event.GetValue().scancode == 20))
            {
                is_running = false;
            }
            else if (event.GetType() == MouseClick)
            {
                printf("%u %u\n", event.GetValue().coordinates.x, event.GetValue().coordinates.y);
            }
        }

        // clock_t start = clock();

        renderer.Clear();

        renderer.SetColor(kBlue);
        renderer.FillRect(Rectangle{100, 100, 200, 200});
        renderer.SetColor(kRed);
        renderer.DrawRect(Rectangle{100, 100, 200, 200});

        renderer.Present();
    }
}
