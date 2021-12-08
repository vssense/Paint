#include "border.hpp"

Border::Border(Vec2<int> size, Color color, int rounding_size)
    : GUIComponent(new Texture(size.x, size.y), Rectangle{0, 0, size.x, size.y})
{
    Renderer* renderer = Renderer::GetInstance();

    renderer->SetColor(color);

    renderer->DrawRect(texture_, Rectangle{0, 0, size.x, size.y});
}

Border::Border(Texture* to_border, Color color, int rounding_size)
    : GUIComponent(nullptr, Rectangle{0, 0, 0, 0})
{
    Vec2<int> size = static_cast<Vec2<int>>(to_border->GetSize());
    
    texture_ = new Texture(size.x, size.y);
    
    Renderer* renderer = Renderer::GetInstance();

    renderer->SetColor(color);

    renderer->DrawRect(texture_, Rectangle{0, 0, size.x, size.y});
}

bool Border::ProcessMouseEvent(const Event& event)
{
    return false;
}

void Border::Render()
{
    Renderer::GetInstance()->CopyTexture(texture_, parent_->GetPlacement());
}
