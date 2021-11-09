#include "renderer.hpp"
#include "coordinate_system.hpp"

Renderer* Renderer::instance_ = nullptr;

void Renderer::Construct(Window* window)
{
    assert(window);

    if (instance_ == nullptr)
    {
        instance_ = new Renderer(window);
        assert(instance_);
    }
}

Renderer* Renderer::GetInstance()
{
    return instance_;
}

Renderer::Renderer(Window* window)
{
    assert(window);

    renderer_ = SDL_CreateRenderer(window->GetWindow(), -1, SDL_RENDERER_SOFTWARE);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer_);
}

void Renderer::DrawLine(Texture* texture, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    assert(texture);
    SetRenderTarget(texture);
    DrawLine(x1, y1, x2, y2);
}

void Renderer::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    assert(!SDL_RenderDrawLine(renderer_, x1, y1, x2, y2));
}

void Renderer::DrawLine(Texture* texture, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t thickness)
{
    assert(texture);
    SetRenderTarget(texture);
    DrawLine(x1, y1, x2, y2, thickness);
}

void Renderer::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t thickness)
{
    Vec2<float> start(x1, y1);
    Vec2<float> vec(x2 + 0.0 - x1, y2 + 0.0 - y1);
    uint32_t len = static_cast<uint32_t>(vec.GetLength());

    vec.Normalize();

    for (uint32_t i = 0; i < len; ++i)
    {
        DrawCircle(Vec2<uint32_t>(static_cast<uint32_t>(start.x + i * vec.x),
                                  static_cast<uint32_t>(start.y + i * vec.y)), thickness);
    }
}

void Renderer::DrawCircle(Texture* texture, Vec2<uint32_t> center, uint32_t radius)
{
    assert(texture);
    SetRenderTarget(texture);
    DrawCircle(center, radius);
}

void Renderer::DrawCircle(Vec2<uint32_t> center, uint32_t radius)
{
    int sradius = static_cast<int>(radius);
    uint32_t radius_squared = radius * radius;

    for (int x = -sradius; x <= sradius; ++x)
    {
        int y_lenght = sqrt(radius_squared - x * x);
        for (int y = -y_lenght; y <= y_lenght; ++y)
        {
            SetPixel(x + center.x, y + center.y);
            SetPixel(x + center.x, -y + center.y);
        }
    }
}

void Renderer::SetPixel(Texture* texture, uint32_t x, uint32_t y)
{
    assert(texture);
    SetRenderTarget(texture);
    SetPixel(x, y);
}

void Renderer::SetPixel(uint32_t x, uint32_t y)
{
    assert(!SDL_RenderDrawPoint(renderer_, x, y));
}

void Renderer::CopyTexture(Texture* src, Texture* dst)
{
    assert(src);
    assert(dst);

    SetRenderTarget(src);
    CopyTexture(dst);
}

void Renderer::CopyTexture(Texture* texture)
{
    assert(texture);

    assert(!SDL_RenderCopy(renderer_, texture->GetTexture(), NULL, NULL));
}

void Renderer::CopyTexture(Texture* src, Texture* dst, const Rectangle& dst_rect)
{
    assert(src);
    assert(dst);

    SetRenderTarget(src);
    CopyTexture(dst, dst_rect);
}

void Renderer::CopyTexture(Texture* texture, const Rectangle& dst_rect)
{
    assert(texture);
    SDL_Rect dst_rectangle{static_cast<int>(dst_rect.x0), static_cast<int>(dst_rect.y0),
                           static_cast<int>(dst_rect.w),  static_cast<int>(dst_rect.h)};

    assert(!SDL_RenderCopy(renderer_, texture->GetTexture(), NULL, &dst_rectangle));
}

void Renderer::CopyTexture(Texture* src, Texture* dst, const Rectangle& src_rect, const Rectangle& dst_rect)
{
    assert(src);
    assert(dst);

    SetRenderTarget(src);
    CopyTexture(dst, src_rect, dst_rect);
}

void Renderer::CopyTexture(Texture* texture, const Rectangle& src_rect, const Rectangle& dst_rect)
{
    assert(texture);
    SDL_Rect src_rectangle{static_cast<int>(src_rect.x0), static_cast<int>(src_rect.y0),
                           static_cast<int>(src_rect.w),  static_cast<int>(src_rect.h)};

    SDL_Rect dst_rectangle{static_cast<int>(dst_rect.x0), static_cast<int>(dst_rect.y0),
                           static_cast<int>(dst_rect.w),  static_cast<int>(dst_rect.h)};

    assert(!SDL_RenderCopy(renderer_, texture->GetTexture(), &src_rectangle, &dst_rectangle));
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

void Renderer::FillRect(Texture* texture, const Rectangle& rect)
{
    assert(texture);
    SetRenderTarget(texture);
    FillRect(rect);
}

void Renderer::FillRect(const Rectangle& rect)
{
    SDL_Rect rectangle{static_cast<int>(rect.x0), static_cast<int>(rect.y0),
                       static_cast<int>(rect.w),  static_cast<int>(rect.h)};
    assert(!SDL_RenderFillRect(renderer_, &rectangle));
}

void Renderer::DrawRect(Texture* texture, const Rectangle& rect)
{
    assert(texture);
    SetRenderTarget(texture);
    DrawRect(rect);
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
