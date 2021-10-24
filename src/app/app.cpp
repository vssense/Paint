#include "app.hpp"

void App::operator () ()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Window window{};
    Renderer renderer(&window);
    Texture texture(&renderer, 300, 300);

    Font font("fonts/font.ttf", 72);
    Text text(&renderer, &font, "pivo");

    renderer.SetRenderTarget(&texture);

    renderer.SetColor(kBlue);
    renderer.FillRect(Rectangle{0, 0, 300, 300});
    renderer.SetColor(kRed);
    renderer.DrawRect(Rectangle{0, 0, 300, 300});
    text.Render(Vec2<uint32_t>(10, 10));
    
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
