#include "tool_texture.hpp"

void ToolTexture::SetPixel(uint32_t x, uint32_t y, uint32_t color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->SetPixel(texture_, x, y);
}

void ToolTexture::DrawRect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->FillRect(texture_, {static_cast<int>(x1),
                                                 static_cast<int>(y1),
                                                 static_cast<int>(x2),
                                                 static_cast<int>(y2)});
}

void ToolTexture::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawLine(texture_, x1, y1, x2, y2);
}

void ToolTexture::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color,
                           uint32_t thickness)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawLine(texture_, x1, y1, x2, y2, thickness);
}

uint32_t ToolTexture::GetXSize() const
{
    return texture_->GetSize().x;
}
uint32_t ToolTexture::GetYSize() const
{
    return texture_->GetSize().y;
}
