#ifndef _TEXTURE_H_INCLUDED
#define _TEXTURE_H_INCLUDED

#include <SDL.h>
#include "../graphics/color.hpp"
#include "../math/vector2.hpp"

class Renderer;

class Texture
{
public:
    Texture(Renderer* renderer, size_t width, size_t height, uint32_t color = kBlack);
    Texture(Renderer* renderer, const char* path);
    ~Texture();

    SDL_Texture* GetTexture() const { return texture_; }
    Vec2<uint32_t> GetSize() const;

private:
    SDL_Texture* texture_;
};

#endif /* _TEXTURE_H_INCLUDED */
