#ifndef _TEXTURE_H_INCLUDED
#define _TEXTURE_H_INCLUDED

#include <SDL.h>
#include "../graphics/color.hpp"
#include "../math/vector2.hpp"

class Text;

class Texture
{
public:
    Texture(size_t width, size_t height);
    Texture(size_t width, size_t height, uint32_t color);
    Texture(const char* path);
    Texture(Text* text);
    ~Texture();

    SDL_Texture* GetTexture() const { return texture_; }
    Vec2<uint32_t> GetSize() const;

private:
    SDL_Texture* texture_;
};

#endif /* _TEXTURE_H_INCLUDED */
