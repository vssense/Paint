#include "text.hpp"

Font::Font(const char* filename, size_t size) : size_(size)
{
    assert(filename);
    assert(size > 0);

    TTF_Init();

    font_ = TTF_OpenFont(filename, size_);
    assert(font_);
}

Font::~Font()
{
    TTF_CloseFont(font_);
}

Text::Text() : texture_(nullptr), size_(0, 0) {}

Text::Text(Font* font, const char* text, Color color) : Text()
{
    assert(font);
    assert(text);

    Load(font, text, color);
}

void Text::Load(Font* font, const char* text, Color color)
{
    assert(font);
    assert(text);

    Destroy();

    SDL_Surface* load_surface = TTF_RenderText_Blended(font->GetFont(), text, ConvertColor(color));
    assert(load_surface);

    size_.x = load_surface->w;
    size_.y = load_surface->h;

    Renderer* renderer = Renderer::GetInstance();
    assert(renderer);

    texture_ = SDL_CreateTextureFromSurface(renderer->GetRenderer(), load_surface);
    assert(texture_);

    SDL_FreeSurface(load_surface);
}

void Text::Render(Vec2<uint32_t> coordinates)
{
    Renderer* renderer = Renderer::GetInstance();
    assert(renderer);

    SDL_Rect rect{static_cast<int>(coordinates.x), static_cast<int>(coordinates.y),
                  static_cast<int>(size_.x),       static_cast<int>(size_.y)};

    SDL_RenderCopy(renderer->GetRenderer(), texture_, NULL, &rect);
}

void Text::Destroy()
{
    if (texture_ != nullptr)
    {
        SDL_DestroyTexture(texture_);
        size_.x = 0;
        size_.y = 0;
    }
}

Text::~Text()
{
    Destroy();
}