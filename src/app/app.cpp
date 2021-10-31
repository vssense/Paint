#include "app.hpp"

class DefaultHitTest : public IHitTestCommand
{
public:
    DefaultHitTest(const Rectangle& placement) : rect_(placement) {}
    virtual bool Execute(Vec2<uint32_t> position) const override
    {
        return IsInsideRectangle(rect_, position);
    }

    virtual const Rectangle& GetPlaceToRender() const override { return rect_; }
private:
    Rectangle rect_;
};

class MainWindowOnEvent : public IOnMouseEventCommand
{
public:
    MainWindowOnEvent() {}
    virtual bool Execute(Vec2<uint32_t> position, const Event& event) override
    {
        printf("Event!!!!!!\n");
        return true;
    }
};

class Close : public IOnMouseEventCommand
{
public:
    Close(bool* is_running) : is_running_(is_running) { assert(is_running); }
    virtual bool Execute(Vec2<uint32_t> position, const Event& event) override
    {
        if (event.GetType() == kMouseButtonRelease)
        {
            printf("Quit!\n");
            *is_running_ = false;
        }

        return true;
    }
private:
    bool* is_running_;
};

void App::operator () ()
{

    Window window{};
    Renderer renderer(&window);
    bool is_running = true;

    Texture texture(&renderer, kWindowWidth, kWindowHeight);

    Font font("fonts/font.ttf", 14);
    Text text(&renderer, &font, "pivo");

    Texture close(&renderer, "img/close.bmp");

    renderer.SetRenderTarget(&texture);

    renderer.SetColor(kBlue);
    renderer.FillRect(Rectangle{0, 0, kWindowWidth, kWindowHeight});
    renderer.SetColor(kRed);
    renderer.DrawRect(Rectangle{0, 0, kWindowWidth, kWindowHeight});
    text.Render(Vec2<uint32_t>(10, 10));
    // renderer.CopyTexture(&close, Rectangle{kWindowWidth - 30, 0, 30, 30});  
    renderer.SetRenderTarget(NULL);

    GUIComponent* main_window = new GUIComponent(&texture,
                                                 new MainWindowOnEvent(),
                                                 new DefaultHitTest(Rectangle{0, 0,
                                                                              kWindowWidth,
                                                                              kWindowHeight}));

    main_window->AddChild(new GUIComponent(&close,
                                           new Close(&is_running),
                                           new DefaultHitTest(Rectangle{kWindowWidth - 30,
                                                                        0, 30, 30})));
    GUIComponentSystem system(&window, main_window);

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
                {
                    // break;
                }
                case kMouseButtonRelease:
                {
                    system.ProcessMouseEvent(event.GetValue().coordinates, event);
                    break;
                }
                case kMouseMotion:
                {
                    system.ProcessMouseEvent(event.GetValue().motion.start, event);
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
