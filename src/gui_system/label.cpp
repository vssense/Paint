#include "label.hpp"
#include "../graphics/text.hpp"
#include "../math/swap.hpp"

Label::Label(const Rectangle& placement, const char* text, Color text_color)
    : GUIComponent(nullptr, placement),
      text_color_(text_color)
{
    SetText(text);
}

void Label::SetText(const char* text)
{
    Font font("fonts/font.ttf", 2 * placement_.h / 3);
    Text label(&font, text, text_color_);

    Destroy();

    texture_ = new Texture(&label);

    Vec2<int> size = Vec2<int>(texture_->GetSize());
    size.x = Min(size.x, placement_.w);
    size.y = Min(size.y, placement_.h);

    placement_.x0 = placement_.w / 2 - size.x / 2;
    placement_.y0 = placement_.h / 2 - size.y / 2;
    placement_.w  = size.x;
    placement_.h  = size.y;
}

void Label::Destroy()
{
    if (texture_ != nullptr)
    {
        delete texture_;
        texture_ = nullptr;
    }
}
