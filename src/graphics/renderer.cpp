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

void Renderer::DrawLine(float x1, float y1, float x2, float y2)
{
    assert(!SDL_RenderDrawLineF(renderer_, x1, y1, x2, y2));
}

void Renderer::DrawCircle(Vec2<float> center, float radius)
{
    assert(radius >= 0);

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

void Renderer::SetColor(uint32_t color)
{
    assert(!SDL_SetRenderDrawColor(renderer_, GetR(color), GetG(color), GetB(color), GetA(color)));
}

void Renderer::SetPixel(float x, float y)
{
    assert(!SDL_RenderDrawPointF(renderer_, x, y));
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
    SDL_Rect rectangle = { (int)rect.x0, (int)rect.y0, (int)rect.w, (int)rect.h };
    assert(!SDL_RenderFillRect(renderer_, &rectangle));
}

void Renderer::DrawRect(const Rectangle& rect)
{
    float x0 = rect.x0;
    float y0 = rect.y0;
    float x1 = rect.x0 + rect.w;
    float y1 = rect.y0 + rect.h;

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
