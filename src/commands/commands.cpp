#include "commands.hpp"
#include "close_commands.hpp"
#include "button_commands.hpp"
#include "../graphics/text.hpp"

GUIComponent* CreateMainWindowTitle(Renderer* renderer, bool* is_running);
GUIComponent* CreateButton(Renderer* renderer, const char* title, const Rectangle& placement, IOnMouseEventCommand* cmd,
                           uint32_t button_color, uint32_t frame_color = kBlack, uint32_t font_color = kBlack);

GUIComponent* CreatePaintTree(Renderer* renderer, bool* is_running)
{
    assert(renderer);

    Texture* main_texture = new Texture(renderer, kWindowWidth, kWindowHeight, kDarkBlue);
    GUIComponent* main_component = new GUIComponent(main_texture, renderer, nullptr,
                                                    Rectangle{0, 0, kWindowWidth, kWindowHeight});
    renderer->SetRenderTarget(main_texture);
    renderer->SetColor(kBlue);
    renderer->DrawRect(Rectangle{0, 0, kWindowWidth, kWindowHeight});
    renderer->SetRenderTarget(nullptr);


    main_component->AddChild(CreateMainWindowTitle(renderer, is_running));

    return main_component;
}

GUIComponent* CreateMainWindowTitle(Renderer* renderer, bool* is_running)
{
    assert(renderer);

    Texture* title_bg = new Texture(renderer, kWindowWidth, kTitleWidth, kLightPurple);
    GUIComponent* title = new GUIComponent(title_bg, renderer, nullptr,
                                           Rectangle{0, 0, kWindowWidth, kTitleWidth});

    title->AddChild(new GUIComponent("img/close.bmp", renderer,
                                     new MainCloseOnMouseEvent(is_running, "img/close2.bmp", renderer),
                                     Rectangle{kWindowWidth - kTitleWidth, 0, kTitleWidth, kTitleWidth}));

    Rectangle file_button{0, 0, kButtonsLen, kTitleWidth};
    title->AddChild(CreateButton(renderer, "File", file_button,
                                 new ButtonOnMouseEvent(new Texture(renderer, file_button.h, file_button.w, kLightYellow)),
                                 kWhite, kBlue));

    Rectangle view_button{kButtonsLen, 0, kButtonsLen, kTitleWidth};
    title->AddChild(CreateButton(renderer, "View", view_button,
                                 new ButtonOnMouseEvent(new Texture(renderer, file_button.h, file_button.w, kLightYellow)),
                                 kWhite, kBlue));

    Rectangle help_button{kButtonsLen * 2, 0, kButtonsLen, kTitleWidth};
    title->AddChild(CreateButton(renderer, "Help", help_button,
                                 new ButtonOnMouseEvent(new Texture(renderer, file_button.h, file_button.w, kLightYellow)),
                                 kWhite, kBlue));

    return title;
}

GUIComponent* CreateButton(Renderer* renderer, const char* title, const Rectangle& placement, IOnMouseEventCommand* cmd,
                           uint32_t button_color, uint32_t frame_color, uint32_t font_color)
{
    assert(renderer);
    assert(title);

    Font font("fonts/font.ttf", 2 * placement.h / 3);
    Text text(renderer, &font, title, font_color);
    Texture* title_texture = new Texture(renderer, &text);
    Vec2<uint32_t> title_size = title_texture->GetSize();
    
    assert(title_size.x <= placement.w);
    assert(title_size.y <= placement.h);

    Texture* button_texture = new Texture(renderer, placement.w, placement.h, button_color);
    
    renderer->SetRenderTarget(button_texture);
    renderer->SetColor(frame_color);
    renderer->DrawRect(Rectangle{0, 0, placement.w, placement.h});
    renderer->SetRenderTarget(nullptr);

    GUIComponent* button_component = new GUIComponent(button_texture, renderer, cmd, placement);

    button_component->AddChild(new GUIComponent(title_texture, renderer, new DefaultOnEventFalse,
                                                Rectangle{placement.w / 2 - title_size.x / 2,
                                                          placement.h / 2 - title_size.y / 2,
                                                          title_size.x, title_size.y}));

    return button_component;
}