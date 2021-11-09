#ifndef _TEXT_HPP_INCLUDED
#define _TEXT_HPP_INCLUDED

#include "renderer.hpp"
#include <SDL_ttf.h>

class Font
{
public:
    Font(const char* filename, size_t size);
    ~Font();

    TTF_Font* GetFont() const { return font_; }
    size_t    GetSize() const { return size_; }

private:
    TTF_Font* font_;
    size_t size_;
};

class Text
{
public:
    Text();
    Text(Font* font, const char* text, uint32_t color = kBlack);
    ~Text();

    void Destroy();
    void Load(Font* font, const char* text, uint32_t color = kBlack);
    void Render(Vec2<uint32_t> coordinates);
    SDL_Texture* GetTexture() const { return texture_; }

private:
    SDL_Texture* texture_;
    Vec2<uint32_t> size_;
};

#endif /* _TEXT_HPP_INCLUDED */