#include "app.hpp"

void App::operator () ()
{
    Window window{};
    Renderer renderer(&window);
    Texture texture(&renderer, 100, 100);

    renderer.SetRenderTarget(&texture);

    renderer.SetColor(kBlue);
    renderer.FillRect(Rectangle{0, 0, 100, 100});
    renderer.SetColor(kRed);
    renderer.DrawRect(Rectangle{0, 0, 100, 100});
    
    renderer.SetRenderTarget(NULL);

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

        renderer.CopyTexture(&texture, Rectangle{200, 200, 300, 300});

        renderer.Present();
    }
}
