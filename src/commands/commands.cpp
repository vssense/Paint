#include "commands.hpp"
#include "close_commands.hpp"

GUIComponent* CreatePaintTree(Renderer* renderer, bool* is_running)
{
    assert(renderer);

    Texture* main_texture = new Texture(renderer, kWindowWidth, kWindowHeight, kGray);
    GUIComponent* main_component = new GUIComponent(main_texture, renderer, nullptr,
                                                    Rectangle{0, 0, kWindowWidth, kWindowHeight});

    Texture* close_texture = new Texture(renderer, "img/close.bmp");

    main_component->AddChild(new GUIComponent(close_texture, renderer,
                                              new MainCloseOnMouseEvent(is_running),
                                              Rectangle{kWindowWidth - 30, 0, 30, 30}));

    return main_component;
}