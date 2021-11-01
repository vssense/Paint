#include "texture.hpp"
#include "renderer.hpp"

Texture::Texture(Renderer* renderer, size_t width, size_t height, uint32_t color)
{
    texture_ = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET,
                                 static_cast<int>(width),
                                 static_cast<int>(height));

    if (color != kBlack)
    {
        renderer->SetRenderTarget(this);
        renderer->SetColor(color);
        renderer->FillRect(Rectangle{0, 0, static_cast<uint32_t>(width), static_cast<uint32_t>(height)});
        renderer->SetRenderTarget(nullptr);
    }
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture_);
}

Texture::Texture(Renderer* renderer, const char* path)
{
    assert(path);

    SDL_Surface* surface = SDL_LoadBMP(path);
    if (surface == nullptr)
    {
        printf("Can't load bmp from %s\n", path);
        assert(0);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->GetRenderer(), surface);
    assert(texture);

    texture_ = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET,
                                 surface->w, surface->h);            
    assert(texture_);

    SDL_SetRenderTarget(renderer->GetRenderer(), texture_);
    SDL_RenderCopy(renderer->GetRenderer(), texture, NULL, NULL);
    SDL_SetRenderTarget(renderer->GetRenderer(), NULL);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

Vec2<uint32_t> Texture::GetSize() const
{
    int width = 0;
    int height = 0;

    assert(!SDL_QueryTexture(texture_, NULL, NULL, &width, &height));

    return Vec2<uint32_t>(width, height);
}
