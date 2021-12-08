#include "label.hpp"
#include "../graphics/text.hpp"
#include "../math/swap.hpp"

Label::Label(const Rectangle& placement, const char* text, Color text_color)
    : GUIComponent(nullptr, placement),
      text_color_(text_color),
      max_size_(placement_)
{
    SetText(text);
}

void Label::SetText(const char* text)
{
    Font font("fonts/font.ttf", 2 * max_size_.h / 3);
    Text label(&font, text, text_color_);

    Destroy();

    texture_ = new Texture(&label);

    Vec2<int> size = Vec2<int>(texture_->GetSize());
    size.x = Min(size.x, max_size_.w);
    size.y = Min(size.y, max_size_.h);

    placement_.x0 = max_size_.w / 2 - size.x / 2;
    placement_.y0 = max_size_.h / 2 - size.y / 2;
    placement_.w  = size.x;
    placement_.h  = size.y;


    placement_.x0 += max_size_.x0;
    placement_.y0 += max_size_.y0;
}

void Label::Move(Vec2<int> d)
{
    placement_.x0 += d.x;
    placement_.y0 += d.y;

    max_size_.x0 += d.x;
    max_size_.y0 += d.y;

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        (*it)->Move(d);
    }
}

void Label::Destroy()
{
    if (texture_ != nullptr)
    {
        delete texture_;
        texture_ = nullptr;
    }
}
