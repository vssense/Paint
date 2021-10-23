#include "renderer.hpp"
#include "coordinate_system.hpp"

uint8_t  GetB(uint32_t color);
uint8_t  GetG(uint32_t color);
uint8_t  GetR(uint32_t color);
uint8_t  GetA(uint32_t color);

Renderer::Renderer(Window* window)
{
    assert(window);

    renderer_ = SDL_CreateRenderer(window->GetWindow(), -1, 0);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer_);
}

void Renderer::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    assert(!SDL_RenderDrawLine(renderer_, x1, y1, x2, y2));
}

void Renderer::DrawCircle(Vec2<uint32_t> center, uint32_t radius)
{
    float radius_squared = radius * radius;

    for (float x = - radius; x <= radius; x++)
    {
        float y_lenght = sqrt(radius_squared - x * x);
        for (float y = -y_lenght; y <= y_lenght; y++)
        {
            SetPixel(x + center.x, y + center.y);
            SetPixel(x + center.x, -y + center.y);
        }
    }
}

void Renderer::SetPixel(uint32_t x, uint32_t y)
{
    assert(!SDL_RenderDrawPointF(renderer_, x, y));
}

void Renderer::CopyTexture(Texture* texture, const Rectangle& dst_rect)
{
    assert(texture);
    SDL_Rect dst_rectangle{static_cast<int>(dst_rect.x0), static_cast<int>(dst_rect.y0), static_cast<int>(dst_rect.w), static_cast<int>(dst_rect.h)};

    SDL_RenderCopy(renderer_, texture->GetTexture(), NULL, &dst_rectangle);
}

void Renderer::CopyTexture(Texture* texture, const Rectangle& src_rect, const Rectangle& dst_rect)
{
    assert(texture);
    SDL_Rect src_rectangle{static_cast<int>(src_rect.x0), static_cast<int>(src_rect.y0), static_cast<int>(src_rect.w), static_cast<int>(src_rect.h)};

    SDL_Rect dst_rectangle{static_cast<int>(dst_rect.x0), static_cast<int>(dst_rect.y0), static_cast<int>(dst_rect.w), static_cast<int>(dst_rect.h)};

    SDL_RenderCopy(renderer_, texture->GetTexture(), &src_rectangle, &dst_rectangle);
}

void Renderer::SetColor(uint32_t color)
{
    assert(!SDL_SetRenderDrawColor(renderer_, GetR(color), GetG(color), GetB(color), GetA(color)));
}

void Renderer::SetRenderTarget(Texture* texture)
{
    if (texture == nullptr)
    {
        assert(!SDL_SetRenderTarget(renderer_, NULL));
    }
    else
    {
        assert(!SDL_SetRenderTarget(renderer_, texture->GetTexture()));
    }
}

void Renderer::Clear()
{
    SetColor(kWhite);
    assert(!SDL_RenderClear(renderer_));
}

void Renderer::Present()
{
    SDL_RenderPresent(renderer_);
}

void Renderer::FillRect(const Rectangle& rect)
{
    SDL_Rect rectangle{static_cast<int>(rect.x0), static_cast<int>(rect.y0), static_cast<int>(rect.w), static_cast<int>(rect.h)};
    assert(!SDL_RenderFillRect(renderer_, &rectangle));
}

void Renderer::DrawRect(const Rectangle& rect)
{
    uint32_t x0 = rect.x0;
    uint32_t y0 = rect.y0;
    uint32_t x1 = rect.x0 + rect.w - 1;
    uint32_t y1 = rect.y0 + rect.h - 1;

    DrawLine(x0, y0, x1, y0);
    DrawLine(x0, y0, x0, y1);
    DrawLine(x1, y1, x1, y0);
    DrawLine(x1, y1, x0, y1);
}

uint8_t GetB(uint32_t color)
{
    return color & 0xFF;
}

uint8_t GetG(uint32_t color)
{
    return (color >> kByteSize) & 0xFF;
}

uint8_t GetR(uint32_t color)
{
    return (color >> (2 * kByteSize)) & 0xFF;
}

uint8_t GetA(uint32_t color)
{
    return (color >> (3 * kByteSize)) & 0xFF;
}
