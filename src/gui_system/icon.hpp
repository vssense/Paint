#ifndef _ICON_HPP_INCLUDED
#define _ICON_HPP_INCLUDED

#include "gui_component.hpp"
#include "../graphics/text.hpp"
#include "../math/swap.hpp"

class Icon : public GUIComponent
{
public:
    Icon(Texture* texture, const Rectangle& placement)
        : GUIComponent(texture, placement)
    {
        assert(texture_);

        Vec2<int> size = Vec2<int>(texture_->GetSize());

        size.x = Min(size.x, placement.w);
        size.y = Min(size.y, placement.h);

        placement_.x0 = placement.w / 2 - size.x / 2;
        placement_.y0 = placement.h / 2 - size.y / 2;
        placement_.w  = size.x;
        placement_.h  = size.y;
    }

    virtual bool ProcessMouseEvent(const Event& event) override
    {
        return false;        
    }
};

class TextIcon : public GUIComponent
{
public:
    TextIcon(const Rectangle& placement, const char* text, uint32_t font_color) : GUIComponent(nullptr, placement)
    {
        assert(text);

        Font font("fonts/font.ttf", 2 * placement.h / 3);
        Text title(&font, text, font_color);
        texture_ = new Texture(&title);

        Vec2<int> size = Vec2<int>(texture_->GetSize());
        size.x = Min(size.x, placement.w);
        size.y = Min(size.y, placement.h);

        placement_.x0 = placement.w / 2 - size.x / 2;
        placement_.y0 = placement.h / 2 - size.y / 2;
        placement_.w  = size.x;
        placement_.h  = size.y;
    }

    virtual bool ProcessMouseEvent(const Event& event) override
    {
        return false;        
    }
};

#endif /* _ICON_HPP_INCLUDED */