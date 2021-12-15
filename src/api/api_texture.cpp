#include "api_texture.hpp"
#include "../graphics/texture_manager.hpp"

ITexture* APITextureFactory::CreateTexture(const char* filename)
{
    return new APITexture(TextureManager::GetInstance()->GetTexture(filename));
}

ITexture* APITextureFactory::CreateTexture(int32_t width, int32_t height)
{
    return new APITexture(new Texture(width, height));
}

int32_t APITexture::GetWidth()
{
    return texture_->GetSize().x;
}

int32_t APITexture::GetHeight()
{
    return texture_->GetSize().y;
}

Buffer APITexture::ReadBuffer()
{
    return Buffer{texture_->ReadBuffer(), this};
}

void APITexture::ReleaseBuffer(Buffer buffer)
{
    assert(this == buffer.texture);

    texture_->ReleaseBuffer(buffer.pixels);
}

void APITexture::LoadBuffer(Buffer buffer)
{
    assert(this == buffer.texture);

    texture_->LoadBuffer(buffer.pixels);
}

void APITexture::Clear(Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->FillRect(texture_, Rectangle{0, 0, GetWidth(), GetHeight()});
}

void APITexture::Present() {}

void APITexture::DrawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawLine(texture_, x0, y0, x1, y1);
}

void APITexture::DrawThickLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t thickness, Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawLine(texture_, x0, y0, x1, y1, thickness);
}

void APITexture::DrawCircle(int32_t x, int32_t y, int32_t radius, Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawCircle(texture_, Vec2<int>(x, y), radius);
}

void APITexture::DrawRect(int32_t x, int32_t y, int32_t width, int32_t height, Color color)
{
    Renderer::GetInstance()->SetColor(color);
    Renderer::GetInstance()->DrawRect(texture_, Rectangle{x, y, width, height});
}

void APITexture::CopyTexture(ITexture* texture, int32_t x, int32_t y, int32_t width, int32_t height)
{
    Renderer::GetInstance()->SetRenderTarget(texture_);

    APITexture* api_texture = dynamic_cast<APITexture*>(texture);
    Renderer::GetInstance()->CopyTexture(api_texture->texture_, Rectangle{x, y, width, height});
}
