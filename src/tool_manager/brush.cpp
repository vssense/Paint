#include "brush.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderer.hpp"

void Brush::BeginDraw(Texture* texture, Vec2<int> coordinates)
{
    assert(texture);
    
    Renderer::GetInstance()->SetColor(color_);
    Renderer::GetInstance()->DrawCircle(texture, coordinates, thickness_);
}

void Brush::Draw(Texture* texture, Vec2<int> start, Vec2<int> displacement)
{
    assert(texture);

    Vec2<int> end = start + displacement;

    Renderer::GetInstance()->SetColor(color_);
    Renderer::GetInstance()->DrawLine(texture, start.x, start.y, end.x, end.y, thickness_);
}

void Brush::EndDraw(Texture* texture, Vec2<int> coordinates)
{
    assert(texture);

    Renderer::GetInstance()->SetColor(color_);
    Renderer::GetInstance()->DrawCircle(texture, coordinates, thickness_);
}
