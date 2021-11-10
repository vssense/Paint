#include "button.hpp"

BasicButton::BasicButton(const Rectangle& placement, ICommand* command, Texture* texture) :
    GUIComponent(texture, placement), command_(command)
{
    assert(command_);
    assert(texture_);
}

BasicButton::BasicButton(const Rectangle& placement, ICommand* command, uint32_t bg, uint32_t border) :
    BasicButton(placement, command, new Texture(placement.w, placement.h, bg, border))
{
    assert(command);
}

BasicButton::BasicButton(const Rectangle& placement, ICommand* command, uint32_t bg,
                         uint32_t border, Texture* icon) :
    BasicButton(placement, command, bg, border)
{
    assert(command);
    assert(icon);
    Attach(new Icon(icon, placement_));
}

BasicButton::BasicButton(const Rectangle& placement, ICommand* command, uint32_t bg,
                         uint32_t border, const char* text, uint32_t font_color) :
    BasicButton(placement, command, bg, border)
{
    assert(command);
    assert(text);

    Attach(new TextIcon(placement, text, font_color));
}

bool BasicButton::ProcessMouseEvent(const Event& event)
{
    if (event.GetType() == kMouseButtonRelease)
    {
        command_->Execute();
    }

    return true;
}

BasicButton::~BasicButton()
{
    assert(command_);

    delete command_;
}

Button::Button(const Rectangle& placement, ICommand* command, Texture* on_release,
               Texture* on_press, Texture* on_hover) :
    BasicButton(placement, command, on_release), on_release_(on_release),
    on_press_(on_press), on_hover_(on_hover)
{
    assert(on_release_);
}

Button::Button(const Rectangle& placement, ICommand* command, Color on_release, Color on_press,
               Color on_hover, const char* text, Color font_color) :
    BasicButton(placement, command, new Texture(placement.w, placement.h, on_release))
{
    assert(command_);
    assert(texture_);

    on_release_ = texture_;
    on_press_   = new Texture(placement_.w, placement_.h, on_press);
    on_hover_   = new Texture(placement_.w, placement_.h, on_hover);

    Attach(new TextIcon(placement, text, font_color));
}

Button::~Button()
{
    texture_ = on_release_;

    if (on_press_ != nullptr)
    {
        delete on_press_;
    }

    if (on_hover_ != nullptr)
    {
        delete on_hover_;
    }
}

bool Button::ProcessMouseEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonRelease:
        {
            texture_ = on_release_;
            command_->Execute();
            break;
        }
        case kMouseButtonPress:
        {
            if (on_press_ != nullptr)
            {
                texture_ = on_press_;
            }
            break;
        }
        case kMouseHover:
        {
            if (on_hover_ != nullptr)
            {
                texture_ = on_hover_;
            }
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}