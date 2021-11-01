#include "commands.hpp"
#include "close_commands.hpp"

GUIComponent* CreateMainWindowTitle(Renderer* renderer, bool* is_running);

GUIComponent* CreatePaintTree(Renderer* renderer, bool* is_running)
{
    assert(renderer);

    Texture* main_texture = new Texture(renderer, kWindowWidth, kWindowHeight, kGray);
    GUIComponent* main_component = new GUIComponent(main_texture, renderer, nullptr,
                                                    Rectangle{0, 0, kWindowWidth, kWindowHeight});

    main_component->AddChild(CreateMainWindowTitle(renderer, is_running));

    return main_component;
}

GUIComponent* CreateMainWindowTitle(Renderer* renderer, bool* is_running)
{
    assert(renderer);

    Texture* title_bg = new Texture(renderer, kWindowWidth, 30, kLightPurple);
    GUIComponent* title = new GUIComponent(title_bg, renderer, nullptr,
                                           Rectangle{0, 0, kWindowWidth, 30});

    title->AddChild(new GUIComponent("img/close.bmp", renderer,
                                     new MainCloseOnMouseEvent(is_running, "img/close2.bmp", renderer),
                                     Rectangle{kWindowWidth - 30, 0, 30, 30}));
    return title;
}