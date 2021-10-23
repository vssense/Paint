#ifndef _TEXTURE_H_INCLUDED
#define _TEXTURE_H_INCLUDED

#include <SDL.h>

class Renderer;

class Texture
{
public:
    Texture() = delete;
    Texture(Renderer* renderer, size_t width, size_t height);
    ~Texture();

    SDL_Texture* GetTexture() { return texture_; }

private:
    SDL_Texture* texture_;
};

#endif /* _TEXTURE_H_INCLUDED */
