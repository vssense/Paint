#include "app.hpp"

class MainWindowHitTest : public IHitTestCommand
{
public:
    MainWindowHitTest(const Rectangle& placement) : rect_(placement) {}
    virtual bool Execute(Vec2<uint32_t> click) const override
    {
        return IsInsideRectangle(rect_, click);
    }

    virtual const Rectangle& GetPlaceToRender() const override { return rect_; }
private:
    Rectangle rect_;
};

class MainWindowOnEvent : public IOnEventCommand
{
public:
    MainWindowOnEvent() {}
    virtual bool Execute(const Event& event) override
    {
        printf("Event!!!!!!\n");
        return true;
    }
};

void App::operator () ()
{
    Window window{};
    Renderer renderer(&window);
    Texture texture(&renderer, kWindowWidth, kWindowHeight);

    Font font("fonts/font.ttf", 14);
    Text text(&renderer, &font, "pivo");

    renderer.SetRenderTarget(&texture);

    renderer.SetColor(kBlue);
    renderer.FillRect(Rectangle{0, 0, kWindowWidth, kWindowHeight});
    renderer.SetColor(kRed);
    renderer.DrawRect(Rectangle{0, 0, kWindowWidth, kWindowHeight});
    text.Render(Vec2<uint32_t>(10, 10));    
    renderer.SetRenderTarget(NULL);

    MainWindowHitTest hit_test(Rectangle{0, 0, kWindowWidth, kWindowHeight});
    MainWindowOnEvent on_event{};

    GUIComponent main_window(&texture, &hit_test, &on_event);

    GUIComponentSystem system(&window, &main_window);

    bool is_running = true;

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
                    // syste
                    // printf("pressed  %u %u\n", event.GetValue().coordinates.x,
                    //                            event.GetValue().coordinates.y);
                    // break;
                }
                case kMouseButtonRelease:
                {
                    // printf("released %u %u\n", event.GetValue().coordinates.x,
                    //                            event.GetValue().coordinates.y);
                    // break;
                }
                case kMouseMotion:
                {
                    system.ProcessEvent(event);
                    // printf("moved    %u %u : %d %d\n", event.GetValue().motion.start.x,
                    //                                    event.GetValue().motion.start.y,
                    //                                    event.GetValue().motion.d.x,
                    //                                    event.GetValue().motion.d.y);
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

        system.Render(&renderer);

        // renderer.CopyTexture(&texture);

        renderer.Present();
    }
}
