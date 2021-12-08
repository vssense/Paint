#ifndef _RENDERER_HPP_INCLUDED
#define _RENDERER_HPP_INCLUDED

#include "color.hpp"
#include "texture.hpp"
#include "window.hpp"
#include "../instruments/plugin_manager.hpp"
#include "../instruments/instrument_manager.hpp"
#include "../math/rectangle.hpp"
#include "../math/vector2.hpp"

class Renderer
{
private:
    Renderer(Window* window);
    ~Renderer();

public:
    static Renderer* GetInstance();
    static void      Construct(Window* window);
    static void      Destruct();

    void DrawLine(Texture* texture, int x1, int y1, int x2, int y2, uint32_t thickness);
    void DrawLine(int x1, int y1, int x2, int y2, uint32_t thickness);

    void DrawLine(Texture* texture, int x1, int y1, int x2, int y2);
    void DrawLine(int x1, int y1, int x2, int y2);

    void DrawCircle(Texture* texture, Vec2<int> center, uint32_t radius);
    void DrawCircle(Vec2<int> center, uint32_t radius);

    void FillRect(Texture* texture, const Rectangle& rect);
    void FillRect(const Rectangle& rect);

    void DrawRect(Texture* texture, const Rectangle& rect);
    void DrawRect(const Rectangle& rect);

    void SetPixel(Texture* texture, int x, int y);
    void SetPixel(int x, int y);

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
