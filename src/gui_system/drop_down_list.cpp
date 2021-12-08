#include "drop_down_list.hpp"

DropDownList::DropDownList(const Rectangle& placement, uint32_t button_height,
                           Color button_color, Color button_hover_color)
    : GUIComponent(new Texture(placement.w, placement.h), placement),
      current_height_(0),
      button_height_(button_height),
      button_color_(button_color),
      button_hover_color_(button_hover_color),
      is_hidden_(true) {}

void DropDownList::AttachButton(const char* title, ICommand* command, ICommand* right_button_press)
{
    if (button_height_ + current_height_ > placement_.h)
    {
        return;
    }

    Button* button = new Button(Rectangle{0, 0 + current_height_, placement_.w, button_height_},
                                command,
                                button_color_,
                                button_hover_color_,
                                button_hover_color_,
                                title, kBlack);

    button->AddBorder(kBlack);
    button->SetRightButtonPressedCommand(right_button_press);

    Attach(button);

    current_height_ += button_height_;
}

bool DropDownList::ProcessListenerEvent(const Event& event)
{
    if (!HitTest(event.GetValue().mouse.coordinates))
    {
        system_->Unsubscribe(kMouseButtonPress);
        is_hidden_ = true;
        return false;
    }

    return OnMouseEvent(event);
}

bool DropDownList::OnMouseEvent(const Event& event)
{
    if (!HitTest(event.GetValue().mouse.coordinates))
    {
        return false;
    }

    for (GUIComponent* child : children_)
    {
        if (child->OnMouseEvent(event))
        {
            return true;
        }
    }

    return ProcessMouseEvent(event);
}

bool DropDownList::HitTest(Vec2<int> coordinates) const
{
    if (is_hidden_)
    {
        return false;
    }

    return IsInsideRectangle(Rectangle{placement_.x0, placement_.y0,
                                       placement_.w, current_height_}, coordinates);
}

void DropDownList::Render()
{
    if (is_hidden_)
    {
        return;
    }

    if (texture_ != nullptr)
    {
        Renderer::GetInstance()->CopyTexture(texture_, placement_);
    }

    for (auto it = children_.end(); it != children_.begin();)
    {
        --it;
        (*it)->Render();
    }
}

void DropDownList::Hide()
{
    is_hidden_ = true;
}

void DropDownList::Show()
{
    is_hidden_ = false;
    system_->Subscribe(this, kMouseButtonPress);
}

void DropDownList::ChangeVisibility()
{
    if (is_hidden_)
    {
        Show();
    }
    else
    {
        Hide();
    }
}