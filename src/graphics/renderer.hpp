#ifndef _RENDERER_HPP_INCLUDED
#define _RENDERER_HPP_INCLUDED

#include "window.hpp"
#include "texture.hpp"
#include "../math/vector2.hpp"

const uint32_t kBlack       = 0x00'00'00'00;
const uint32_t kWhite       = 0x00'FF'FF'FF;
const uint32_t kLightPurple = 0x00'E1'E1'FA;
const uint32_t kDarkGray    = 0x00'40'40'40;
const uint32_t kLightYellow = 0x00'FF'EE'91;
const uint32_t kYellow      = 0x00'FF'E6'00;
const uint32_t kBlue        = 0x00'00'80'FF;
const uint32_t kGray        = 0x00'66'66'66;
const uint32_t kRed         = 0x00'FD'59'59;

const size_t kByteSize = 8;

#include "../math/rectangle.hpp"

class Renderer
{
public:
    Renderer() = delete;
    Renderer(Window* window);
    ~Renderer();

    void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
    void DrawCircle(Vec2<uint32_t> center, uint32_t radius);

    void FillRect(const Rectangle& rect);
    void DrawRect(const Rectangle& rect);
    void SetPixel(uint32_t x, uint32_t y);

    void CopyTexture(Texture* texture, const Rectangle& dst_rect);
    void CopyTexture(Texture* texture, const Rectangle& src_rect, const Rectangle& dst_rect);

    void SetColor(uint32_t color);
    void SetRenderTarget(Texture* texture);
    void Clear();
    void Present();

    SDL_Renderer* GetRenderer() { return renderer_; }

private:
    SDL_Renderer* renderer_;
};

#endif /* _RENDERER_HPP_INCLUDED */
