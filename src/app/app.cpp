#include "app.hpp"

void App::operator () ()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Window window{};
    Renderer renderer(&window);
    Texture texture(&renderer, 300, 300);

    Font font("fonts/font.ttf", 32);
    Text text(&renderer, &font, "pivo");

    renderer.SetRenderTarget(&texture);

    renderer.SetColor(kBlue);
    renderer.FillRect(Rectangle{0, 0, 300, 300});
    renderer.SetColor(kRed);
    renderer.DrawRect(Rectangle{0, 0, 300, 300});
    
    renderer.SetRenderTarget(NULL);

    bool is_running = true;

    int i = 0;

    while (is_running)
    {
        Event event;
        while (event.PollEvent())
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
                {
                    printf("pressed  %u %u\n", event.GetValue().coordinates.x,
                                               event.GetValue().coordinates.y);
                    break;
                }
                case kMouseButtonRelease:
                {
                    printf("released %u %u\n", event.GetValue().coordinates.x,
                                               event.GetValue().coordinates.y);
                    break;
                }
                case kMouseMotion:
                {
                    printf("moved    %u %u : %d %d\n", event.GetValue().motion.end.x,
                                                       event.GetValue().motion.end.y,
                                                       event.GetValue().motion.d.x,
                                                       event.GetValue().motion.d.y);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        // clock_t start = clock();

        renderer.Clear();

        renderer.CopyTexture(&texture, Rectangle{200, 200, 300, 300});
        text.Render(Vec2<uint32_t>(200, 200));
        char str[100] = "";
        text.Load(&font, SDL_itoa(i++, str, 10));

        renderer.Present();
    }
}
