#ifndef _RENDERER_HPP_INCLUDED
#define _RENDERER_HPP_INCLUDED

#include "color.hpp"
#include "texture.hpp"
#include "window.hpp"
#include "../math/rectangle.hpp"
#include "../math/vector2.hpp"

class Renderer
{
public:
    static Renderer* GetInstance();
    static void      Construct(Window* window);
private:
    Renderer(Window* window);

public:
    ~Renderer();

    void DrawLine(Texture* texture, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t thickness);
    void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t thickness);

    void DrawLine(Texture* texture, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
    void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

    void DrawCircle(Texture* texture, Vec2<uint32_t> center, uint32_t radius);
    void DrawCircle(Vec2<uint32_t> center, uint32_t radius);

    void FillRect(Texture* texture, const Rectangle& rect);
    void FillRect(const Rectangle& rect);

    void DrawRect(Texture* texture, const Rectangle& rect);
    void DrawRect(const Rectangle& rect);

    void SetPixel(Texture* texture, uint32_t x, uint32_t y);
    void SetPixel(uint32_t x, uint32_t y);

    void CopyTexture(Texture* src, Texture* dst);
    void CopyTexture(Texture* texture);

    void CopyTexture(Texture* src, Texture* dst, const Rectangle& dst_rect);
    void CopyTexture(Texture* texture, const Rectangle& dst_rect);

    void CopyTexture(Texture* src, Texture* dst, const Rectangle& src_rect, const Rectangle& dst_rect);
    void CopyTexture(Texture* texture, const Rectangle& src_rect, const Rectangle& dst_rect);

    void SetColor(uint32_t color);
    void SetRenderTarget(Texture* texture);
    void Clear();
    void Present();

    SDL_Renderer* GetRenderer() const { return renderer_; }

private:
    static Renderer* instance_;
    SDL_Renderer* renderer_;
};

#endif /* _RENDERER_HPP_INCLUDED */
