#include "commands.hpp"
#include "close_commands.hpp"
#include "button_commands.hpp"
#include "canvas_commands.hpp"
#include "../gui_component_system/brush_commands.hpp"
#include "../graphics/text.hpp"
#include "../gui_component_system/default_commands.hpp"

GUIComponent* CreatePaintTree(Renderer* renderer, bool* is_running, GUIComponentSystem* system)
{
    assert(renderer);

    Texture* main_texture = new Texture(renderer, kWindowWidth, kWindowHeight);
    Texture picture(renderer, "img/pic.bmp");

    GUIComponent* main_component = new GUIComponent(main_texture, renderer, nullptr,
                                                    Rectangle{0, 0, kWindowWidth, kWindowHeight});
    renderer->SetColor(kBlue);
    renderer->CopyTexture(main_texture, &picture, Rectangle{0, 0, kWindowWidth, kWindowHeight});
    renderer->DrawRect(main_texture, Rectangle{0, 0, kWindowWidth, kWindowHeight});

    main_component->AddChild(CreateMainWindowTitle(renderer, main_component, is_running, kWindowWidth, kTitleWidth, system));
    main_component->AddChild(CreatePalette(renderer, kPalettePlacement, system));

    return main_component;
}

GUIComponent* CreateMainWindowTitle(Renderer* renderer, GUIComponent* main_component, bool* is_running, uint32_t len, uint32_t width, GUIComponentSystem* system)
{
    assert(renderer);

    GUIComponent* title = new GUIComponent(new Texture(renderer, len, width, kLightPurple),
                                           renderer, nullptr, Rectangle{0, 0, len, width});

    title->AddChild(new GUIComponent("img/close.bmp", renderer,
                                     new MainCloseOnMouseEvent(is_running, "img/close2.bmp", renderer),
                                     Rectangle{len - width, 0, width, width}));

    Rectangle file_button{0, 0, kButtonsLen, width};
    title->AddChild(CreateButton(renderer, "File", file_button,
                                 new ButtonFileOnMouseEvent(new Texture(renderer, file_button.h, file_button.w, kLightYellow)),
                                 kWhite, kBlue));

    Rectangle view_button{kButtonsLen, 0, kButtonsLen, width};
    title->AddChild(CreateButton(renderer, "View", view_button,
                                 new ButtonViewOnMouseEvent(new Texture(renderer, file_button.h, file_button.w,
                                                            kLightYellow), main_component, system), kWhite, kBlue));

    Rectangle help_button{kButtonsLen * 2, 0, kButtonsLen, width};
    title->AddChild(CreateButton(renderer, "Help", help_button,
                                 new ButtonHelpOnMouseEvent(new Texture(renderer, file_button.h, file_button.w, kLightYellow)),
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
    
    renderer->SetColor(frame_color);
    renderer->DrawRect(button_texture, Rectangle{0, 0, placement.w, placement.h});

    GUIComponent* button_component = new GUIComponent(button_texture, renderer, cmd, placement);

    button_component->AddChild(new GUIComponent(title_texture, renderer, new DefaultOnEventFalse,
                                                Rectangle{placement.w / 2 - title_size.x / 2,
                                                          placement.h / 2 - title_size.y / 2,
                                                          title_size.x, title_size.y}));
    return button_component;
}

GUIComponent* CreateCanvas(Renderer* renderer, const Rectangle& placement, GUIComponentSystem* system)
{
    assert(renderer);

    GUIComponent* canvas = new GUIComponent(new Texture(renderer, placement.w, placement.h, kYellow),
                                            renderer, nullptr, placement);

    canvas->AddChild(CreateCanvasTitle(renderer, canvas, placement.w, kTitleWidth));
    canvas->AddChild(CreateScene(renderer, Rectangle{0,
                                                     kTitleWidth,
                                                     placement.w,
                                                     placement.h - kTitleWidth},
                                                     system));
    return canvas;
}

GUIComponent* CreateScene(Renderer* renderer, const Rectangle& placement, GUIComponentSystem* system)
{
    assert(renderer);

    Texture* texture = new Texture(renderer, placement.w, placement.h, kWhite);
    
    renderer->SetColor(kRed);
    renderer->DrawRect(texture, Rectangle{0, 0, placement.w, placement.h});

    return new GUIComponent(texture, renderer, new SceneOnMouseEvent(texture, system), placement);
}

GUIComponent* CreateCanvasTitle(Renderer* renderer, GUIComponent* canvas, uint32_t len, uint32_t width)
{
    assert(renderer);

    GUIComponent* title = new GUIComponent(new Texture(renderer, len, width, kLightPurple),
                                           renderer, new CanvasTitleOnMouseEvent(canvas),
                                           Rectangle{0, 0, len, width});

    Font font("fonts/font.ttf", 2 * width / 3);
    Text text(renderer, &font, "Canvas");
    Texture* text_texture = new Texture(renderer, &text);
    Vec2<uint32_t> text_size = text_texture->GetSize();

    title->AddChild(new GUIComponent("img/close.bmp", renderer,
                                     new CloseCanvasOnMouseEvent(canvas, "img/close2.bmp", renderer),
                                     Rectangle{len - width, 0, width, width}));

    title->AddChild(new GUIComponent(text_texture, renderer, new DefaultOnEventFalse,
                                     Rectangle{len / 2   - text_size.x / 2,
                                               width / 2 - text_size.y / 2,
                                               text_size.x, text_size.y}));

    return title;
}

GUIComponent* CreatePalette(Renderer* renderer, const Rectangle& placement, GUIComponentSystem* system)
{
    assert(renderer);
    assert(system);

    Texture* palette_texture = new Texture(renderer, placement.w, placement.h, kWhite);
    
    renderer->SetColor(kRed);
    renderer->DrawRect(palette_texture, Rectangle{0, 0, placement.w, placement.h});

    GUIComponent* palette = new GUIComponent(palette_texture, renderer, new PaletteOnEvent, placement);

    palette->AddChild(CreatePaletteColor(renderer, Rectangle{10, 10, kColorSquareSize, kColorSquareSize}, kRed, system));
    palette->AddChild(CreatePaletteColor(renderer, Rectangle{40, 10, kColorSquareSize, kColorSquareSize}, kBlue, system));
    palette->AddChild(CreatePaletteColor(renderer, Rectangle{10, 40, kColorSquareSize, kColorSquareSize}, kYellow, system));
    palette->AddChild(CreatePaletteColor(renderer, Rectangle{40, 40, kColorSquareSize, kColorSquareSize}, kLightPurple, system));
    palette->AddChild(CreatePaletteColor(renderer, Rectangle{10, 70, kColorSquareSize, kColorSquareSize}, kWhite, system));
    palette->AddChild(CreatePaletteColor(renderer, Rectangle{40, 70, kColorSquareSize, kColorSquareSize}, kBlack, system));

    return palette;
}

GUIComponent* CreatePaletteColor(Renderer* renderer, const Rectangle& placement, uint32_t color, GUIComponentSystem* system)
{
    Texture* color_texture = new Texture(renderer, kColorSquareSize, kColorSquareSize, color);

    renderer->SetColor(kBlack);
    renderer->DrawRect(color_texture, Rectangle{0, 0, kColorSquareSize, kColorSquareSize});

    return new GUIComponent(color_texture, renderer, new SquareOnEvent(system, color), placement);
}