#include "texture.hpp"
#include "renderer.hpp"

Texture::Texture(Renderer* renderer, size_t width, size_t height)
{
    texture_ = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET,
                                 static_cast<int>(width),
                                 static_cast<int>(height));
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture_);
}