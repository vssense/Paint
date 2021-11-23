#include "brush.hpp"

void Brush::BeginDraw(ITexture* texture, Vec2<int> coordinates)
{
    assert(texture);
    
    // texture->DrawRect(coordinates.x, coordinates.y, thickness_, thickness_);
}

void Brush::Draw(ITexture* texture, Vec2<int> start, Vec2<int> displacement)
{
    assert(texture);

    Vec2<int> end = start + displacement;

    texture->DrawLine(start.x, start.y, end.x, end.y, color_, thickness_);
}

void Brush::EndDraw(ITexture* texture, Vec2<int> coordinates)
{
    assert(texture);

    // Renderer::GetInstance()->SetColor(color_);
    // Renderer::GetInstance()->DrawCircle(texture, coordinates, thickness_);
}
