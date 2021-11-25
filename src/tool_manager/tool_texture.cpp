#include "tool_texture.hpp"

int32_t ToolTexture::GetWidth()
{
    return texture_->GetSize().x;
}

int32_t ToolTexture::GetHeight()
{
    return texture_->GetSize().y;
}

Buffer ToolTexture::ReadBuffer()
{
    return Buffer{texture_->ReadBuffer(), this};
}

void ToolTexture::ReleaseBuffer(Buffer buffer)
{
    assert(this == buffer.texture);

    texture_->ReleaseBuffer(buffer.pixels);
}

void ToolTexture::LoadBuffer(Buffer buffer)
{
    assert(this == buffer.texture);

    texture_->ReleaseBuffer(buffer.pixels);
}


void ToolTexture::Clear(Color color)
{
    Renderer::GetInstance()->FillRect(texture_, Rectangle{0, 0, GetWidth(), GetHeight()});
}

void ToolTexture::Present()
{
    ;
}

void ToolTexture::DrawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawLine(texture_, x0, y0, x1, y1);
}

void ToolTexture::DrawThickLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t thickness, Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawLine(texture_, x0, y0, x1, y1, thickness);
}

void ToolTexture::DrawCircle(int32_t x, int32_t y, int32_t radius, Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawCircle(texture_, Vec2<int>(x, y), radius);
}

void ToolTexture::DrawRect(int32_t x, int32_t y, int32_t width, int32_t height, Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawRect(texture_, Rectangle{x, y, width, height});
}

void ToolTexture::CopyTexture(ITexture* texture, int32_t x, int32_t y,
                              int32_t width, int32_t height)
{
    Renderer::GetInstance()->CopyTexture(texture_, Rectangle{x, y, width, height});
}
