#include "text.hpp"
#include "texture.hpp"
#include "renderer.hpp"

Texture::Texture(uint32_t width, uint32_t height)
    : manager_owns_(false)
{
    texture_ = SDL_CreateTexture(Renderer::GetInstance()->GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET,
                                 static_cast<int>(width),
                                 static_cast<int>(height));

    SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
}

Texture::Texture(uint32_t width, uint32_t height, Color color) :
    Texture(width, height)
{
    Renderer* renderer = Renderer::GetInstance();
    renderer->SetColor(color);
    renderer->FillRect(this, Rectangle{0, 0, static_cast<int>(width), static_cast<int>(height)});
}

Texture::Texture(uint32_t width, uint32_t height, Color bg, Color border) :
    Texture(width, height, bg)
{
    Renderer* renderer = Renderer::GetInstance();
    renderer->SetColor(border);
    renderer->DrawRect(this, Rectangle{0, 0, static_cast<int>(width), static_cast<int>(height)});
}

Texture::Texture(const char* path)
    : texture_(nullptr),
      manager_owns_(false)
{
    assert(path);

    SDL_Surface* surface = SDL_LoadBMP(path);
    if (surface == nullptr)
    {
        printf("Can't load bmp from %s\n", path);
        return;
    }

    Renderer* renderer = Renderer::GetInstance();
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
    SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
}

Texture::Texture(Text* text)
    : manager_owns_(false)
{
    assert(text);

    int width = 0;
    int height = 0;
    SDL_QueryTexture(text->GetTexture(), NULL, NULL, &width, &height);

    Renderer* renderer = Renderer::GetInstance();

    texture_ = SDL_CreateTexture(renderer->GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetRenderTarget(renderer->GetRenderer(), texture_);
    SDL_RenderCopy(renderer->GetRenderer(), text->GetTexture(), NULL, NULL);
    SDL_SetRenderTarget(renderer->GetRenderer(), NULL);
    SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
}

void Texture::SetManagerOwner()
{
    manager_owns_ = true;
}

bool Texture::IsManagerOwner()
{
    return manager_owns_;
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture_);
}

Vec2<uint32_t> Texture::GetSize() const
{
    int width = 0;
    int height = 0;

    assert(!SDL_QueryTexture(texture_, NULL, NULL, &width, &height));

    return Vec2<uint32_t>(width, height);
}

Color* Texture::ReadBuffer()
{
    Vec2<uint32_t> size = GetSize();
    Color* buffer = new Color[size.x * size.y];
    assert(buffer);

    Renderer* renderer = Renderer::GetInstance();
    renderer->SetRenderTarget(this);
    assert(!SDL_RenderReadPixels(renderer->GetRenderer(), NULL, SDL_PIXELFORMAT_RGBA8888,
                                 buffer, size.x * sizeof(Color)));

    return buffer;
}

void Texture::LoadBuffer(Color* buffer)
{
    assert(!SDL_UpdateTexture(texture_, NULL, buffer, GetSize().x * sizeof(Color)));
}

void Texture::ReleaseBuffer(Color* buffer)
{
    delete[] buffer;
}
