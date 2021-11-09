#include "commands.hpp"
#include "close_commands.hpp"
#include "button_commands.hpp"
#include "canvas_commands.hpp"
#include "../paint_gui_system/brush_commands.hpp"
#include "../graphics/text.hpp"
#include "../gui_system/default_commands.hpp"

GUIComponent* CreatePaintTree(bool* is_running, PaintGUISystem* system)
{
    assert(is_running);
    assert(system);

    Renderer* renderer = Renderer::GetInstance();
    assert(renderer);

    Texture* main_texture = new Texture(kWindowWidth, kWindowHeight);
    Texture picture("img/pic.bmp");

    GUIComponent* main_component = new GUIComponent(main_texture, nullptr,
                                                    Rectangle{0, 0, kWindowWidth, kWindowHeight});
    renderer->SetColor(kBlue);
    renderer->CopyTexture(main_texture, &picture, Rectangle{0, 0, kWindowWidth, kWindowHeight});
    renderer->DrawRect(main_texture, Rectangle{0, 0, kWindowWidth, kWindowHeight});

    main_component->AddChild(CreateMainWindowTitle(main_component, is_running, kWindowWidth, kTitleWidth, system));
    main_component->AddChild(CreatePalette(kPalettePlacement, system));

    return main_component;
}

GUIComponent* CreateMainWindowTitle(GUIComponent* main_component, bool* is_running, uint32_t len, uint32_t width, PaintGUISystem* system)
{
    assert(main_component);
    assert(is_running);
    assert(system);

    GUIComponent* title = new GUIComponent(new Texture(len, width, kLightPurple),
                                           nullptr, Rectangle{0, 0, len, width});

    title->AddChild(new GUIComponent("img/close.bmp", new MainCloseOnMouseEvent(is_running, "img/close2.bmp"),
                                     Rectangle{len - width, 0, width, width}));

    Rectangle file_button{0, 0, kButtonsLen, width};
    title->AddChild(CreateButton("File", file_button,
                                 new ButtonFileOnMouseEvent(new Texture(file_button.h, file_button.w, kLightYellow)),
                                 kWhite, kBlue));

    Rectangle view_button{kButtonsLen, 0, kButtonsLen, width};
    title->AddChild(CreateButton("View", view_button,
                                 new ButtonViewOnMouseEvent(new Texture(view_button.h, view_button.w, kLightYellow),
                                                            main_component, system), kWhite, kBlue));

    Rectangle help_button{kButtonsLen * 2, 0, kButtonsLen, width};
    title->AddChild(CreateButton("Help", help_button,
                                 new ButtonHelpOnMouseEvent(new Texture(help_button.h, help_button.w, kLightYellow)),
                                 kWhite, kBlue));
    return title;
}

GUIComponent* CreateButton(const char* title, const Rectangle& placement, IOnMouseEventCommand* cmd,
                           uint32_t button_color, uint32_t frame_color, uint32_t font_color)
{
    assert(title);
    assert(cmd);

    Renderer* renderer = Renderer::GetInstance();
    assert(renderer);

    Font font("fonts/font.ttf", 2 * placement.h / 3);
    Text text(&font, title, font_color);
    Texture* title_texture = new Texture(&text);
    Vec2<uint32_t> title_size = title_texture->GetSize();
    
    assert(title_size.x <= placement.w);
    assert(title_size.y <= placement.h);

    Texture* button_texture = new Texture(placement.w, placement.h, button_color);
    
    renderer->SetColor(frame_color);
    renderer->DrawRect(button_texture, Rectangle{0, 0, placement.w, placement.h});

    GUIComponent* button_component = new GUIComponent(button_texture, cmd, placement);

    button_component->AddChild(new GUIComponent(title_texture, new DefaultOnEventFalse,
                                                Rectangle{placement.w / 2 - title_size.x / 2,
                                                          placement.h / 2 - title_size.y / 2,
                                                          title_size.x, title_size.y}));
    return button_component;
}

GUIComponent* CreateCanvas(const Rectangle& placement, PaintGUISystem* system)
{
    assert(system);

    GUIComponent* canvas = new GUIComponent(new Texture(placement.w, placement.h, kYellow), nullptr, placement);

    canvas->AddChild(CreateCanvasTitle(canvas, placement.w, kTitleWidth));
    canvas->AddChild(CreateScene(Rectangle{0, kTitleWidth, placement.w, placement.h - kTitleWidth}, system));
    return canvas;
}

GUIComponent* CreateScene(const Rectangle& placement, PaintGUISystem* system)
{
    assert(system);
    Renderer* renderer = Renderer::GetInstance();
    assert(renderer);

    Texture* texture = new Texture(placement.w, placement.h, kWhite);
    
    renderer->SetColor(kRed);
    renderer->DrawRect(texture, Rectangle{0, 0, placement.w, placement.h});

    return new GUIComponent(texture, new SceneOnMouseEvent(texture, system), placement);
}

GUIComponent* CreateCanvasTitle(GUIComponent* canvas, uint32_t len, uint32_t width)
{
    assert(canvas);

    GUIComponent* title = new GUIComponent(new Texture(len, width, kLightPurple),
                                           new CanvasTitleOnMouseEvent(canvas),
                                           Rectangle{0, 0, len, width});

    Font font("fonts/font.ttf", 2 * width / 3);
    Text text(&font, "Canvas");
    Texture* text_texture = new Texture(&text);
    Vec2<uint32_t> text_size = text_texture->GetSize();

    title->AddChild(new GUIComponent("img/close.bmp",
                                     new CloseCanvasOnMouseEvent(canvas, "img/close2.bmp"),
                                     Rectangle{len - width, 0, width, width}));

    title->AddChild(new GUIComponent(text_texture, new DefaultOnEventFalse,
                                     Rectangle{len / 2   - text_size.x / 2,
                                               width / 2 - text_size.y / 2,
                                               text_size.x, text_size.y}));

    return title;
}

GUIComponent* CreatePalette(const Rectangle& placement, PaintGUISystem* system)
{
    assert(system);

    Renderer* renderer = Renderer::GetInstance();
    assert(renderer);

    Texture* palette_texture = new Texture(placement.w, placement.h, kWhite);
    
    renderer->SetColor(kRed);
    renderer->DrawRect(palette_texture, Rectangle{0, 0, placement.w, placement.h});

    GUIComponent* palette = new GUIComponent(palette_texture, new PaletteOnEvent, placement);

    palette->AddChild(CreatePaletteColor(Rectangle{10, 10, kColorSquareSize, kColorSquareSize}, kRed, system));
    palette->AddChild(CreatePaletteColor(Rectangle{40, 10, kColorSquareSize, kColorSquareSize}, kBlue, system));
    palette->AddChild(CreatePaletteColor(Rectangle{10, 40, kColorSquareSize, kColorSquareSize}, kYellow, system));
    palette->AddChild(CreatePaletteColor(Rectangle{40, 40, kColorSquareSize, kColorSquareSize}, kLightPurple, system));
    palette->AddChild(CreatePaletteColor(Rectangle{10, 70, kColorSquareSize, kColorSquareSize}, kWhite, system));
    palette->AddChild(CreatePaletteColor(Rectangle{40, 70, kColorSquareSize, kColorSquareSize}, kBlack, system));

    return palette;
}

GUIComponent* CreatePaletteColor(const Rectangle& placement, uint32_t color, PaintGUISystem* system)
{
    assert(system);
    
    Renderer* renderer = Renderer::GetInstance();
    assert(renderer);

    Texture* color_texture = new Texture(kColorSquareSize, kColorSquareSize, color);

    renderer->SetColor(kBlack);
    renderer->DrawRect(color_texture, Rectangle{0, 0, kColorSquareSize, kColorSquareSize});

    return new GUIComponent(color_texture, new SquareOnEvent(system, color), placement);
}