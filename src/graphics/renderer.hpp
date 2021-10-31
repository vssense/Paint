#ifndef _RENDERER_HPP_INCLUDED
#define _RENDERER_HPP_INCLUDED

#include "texture.hpp"
#include "window.hpp"
#include "../math/rectangle.hpp"
#include "../math/vector2.hpp"

const uint32_t kBlack       = 0xFF'00'00'00;
const uint32_t kWhite       = 0xFF'FF'FF'FF;
const uint32_t kLightPurple = 0xFF'E1'E1'FA;
const uint32_t kDarkGray    = 0xFF'40'40'40;
const uint32_t kLightYellow = 0xFF'FF'EE'91;
const uint32_t kYellow      = 0xFF'FF'E6'00;
const uint32_t kBlue        = 0xFF'00'80'FF;
const uint32_t kGray        = 0xFF'66'66'66;
const uint32_t kRed         = 0xFF'FD'59'59;

const size_t kByteSize = 8;

SDL_Color ConvertColor(uint32_t color);

class Renderer
{
public:
    Renderer(Window* window);
    ~Renderer();

    void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
    void DrawCircle(Vec2<uint32_t> center, uint32_t radius);

    void FillRect(const Rectangle& rect);
    void DrawRect(const Rectangle& rect);
    void SetPixel(uint32_t x, uint32_t y);

    void CopyTexture(Texture* texture);
    void CopyTexture(Texture* texture, const Rectangle& dst_rect);
    void CopyTexture(Texture* texture, const Rectangle& src_rect, const Rectangle& dst_rect);

    void SetColor(uint32_t color);
    void SetRenderTarget(Texture* texture);
    void Clear();
    void Present();

    SDL_Renderer* GetRenderer() const { return renderer_; }

private:
    SDL_Renderer* renderer_;
};

#endif /* _RENDERER_HPP_INCLUDED */
