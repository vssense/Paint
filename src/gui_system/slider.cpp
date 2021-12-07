#include "slider.hpp"
#include "gui_system.hpp"

Thumb::Thumb(Vec2<int> size, Texture* texture)
        : GUIComponent(texture, Rectangle{0, 0, size.x, size.y}), slider_(nullptr) {}

Thumb::Thumb(Vec2<int> size)
        : Thumb(size, new Texture(size.x, size.y, kGray, kBlack)) {}

int Thumb::GetWidth() const
{
    return placement_.w;
}

int Thumb::GetHeight() const
{
    return placement_.h;
}

void Thumb::SetSlider(Slider* slider)
{
    slider_ = slider;
}

void Thumb::SetPosition(Vec2<int> position)
{
    Vec2<int> center = placement_.Start();
    Move(position - center);
}

bool Thumb::ProcessListenerEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonRelease:
        {
            system_->Unsubscribe(kMouseButtonRelease);
            system_->Unsubscribe(kMouseMotion);
            break;
        }
        case kMouseMotion:
        case kMouseButtonPress:
        {
            slider_->SetValue(event.GetValue().mouse.coordinates);
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}

bool Thumb::ProcessMouseEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonPress:
        {
            system_->Subscribe(this, kMouseMotion);
            system_->Subscribe(this, kMouseButtonRelease);
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}

Slider::Slider(const Rectangle& placement, Texture* texture, ISliderResponse* callback,
               Thumb* thumb, float range_min, float range_max)
    : GUIComponent(texture, placement),
      thumb_(thumb),
      callback_(callback),
      range_min_(range_min),
      range_max_(range_max),
      cur_value_(range_min)
{
    assert(thumb_);
    assert(callback_);

    Attach(thumb_);
    thumb_->SetSlider(this);

    Renderer::GetInstance()->SetColor(kBlack);
    Renderer::GetInstance()->DrawRect(texture_, Rectangle{0, 0, placement_.w, placement_.h});
}

Slider::~Slider()
{
    delete callback_;
}

float Slider::GetValue() const
{
    return cur_value_;
}

float Slider::GetStep() const
{
    return (range_max_ - range_min_) / (track_.y - track_.x);
}

int Slider::GetTrackStart() const
{
    return track_.x;
}

HorizontalSlider::HorizontalSlider(const Rectangle& rectangle, Texture* texture,
                                   ISliderResponse* callback, Thumb* thumb,
                                   float range_min, float range_max)
    : Slider(rectangle, texture, callback, thumb, range_min, range_max)
{
    track_.x = placement_.x0 + thumb->GetWidth() / 2;
    track_.y = placement_.x0 + placement_.w - thumb->GetWidth() / 2;
}

HorizontalSlider::HorizontalSlider(const Rectangle& placement, Texture* texture,
                                   ISliderResponse* callback, float range_min, float range_max)
    : HorizontalSlider(placement, texture, callback,
                       new Thumb(Vec2<int>(placement.h, placement.h)),
                       range_min, range_max) {}

VerticalSlider::VerticalSlider(const Rectangle& rectangle, Texture* texture,
                               ISliderResponse* callback, Thumb* thumb,
                               float range_min, float range_max)
    : Slider(rectangle, texture, callback, thumb, range_min, range_max)
{
    track_.x = placement_.y0 + thumb->GetHeight() / 2;
    track_.y = placement_.y0 + placement_.h - thumb->GetHeight() / 2;
}

VerticalSlider::VerticalSlider(const Rectangle& placement, Texture* texture,
                               ISliderResponse* callback, float range_min, float range_max)
    : VerticalSlider(placement, texture, callback,
                     new Thumb(Vec2<int>(placement.w, placement.w)),
                     range_min, range_max) {}

bool HorizontalSlider::ProcessMouseEvent(const Event& event)
{
    if (event.GetType() == kMouseButtonPress)
    {
        SetValue((event.GetValue().mouse.coordinates.x - track_.x) * GetStep());
        thumb_->ProcessMouseEvent(event);
    }

    return true;
}

bool VerticalSlider::ProcessMouseEvent(const Event& event)
{
    if (event.GetType() == kMouseButtonPress)
    {
        SetValue((event.GetValue().mouse.coordinates.y - track_.x) * GetStep());
        thumb_->ProcessMouseEvent(event);
    }

    return true;
}

void HorizontalSlider::Move(Vec2<int> d)
{
    placement_.x0 += d.x;
    placement_.y0 += d.y;
    track_.x += d.x;
    track_.y += d.x;

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        (*it)->Move(d);
    }
}

void VerticalSlider::Move(Vec2<int> d)
{
    placement_.x0 += d.x;
    placement_.y0 += d.y;
    track_.x += d.y;
    track_.y += d.y;

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        (*it)->Move(d);
    }
}

void HorizontalSlider::SetValue(float value)
{
    value = std::min(value, range_max_);
    value = std::max(value, range_min_);

    callback_->Respond(cur_value_, value);
    cur_value_ = value;

    thumb_->SetPosition({static_cast<int>((value - range_min_) / GetStep()) + track_.x -
                                          thumb_->GetWidth() / 2, placement_.y0});
}

void HorizontalSlider::SetValue(Vec2<int> coordinates)
{
    SetValue((coordinates.x - track_.x) * GetStep());
}

void VerticalSlider::SetValue(float value)
{
    value = std::min(value, range_max_);
    value = std::max(value, range_min_);

    callback_->Respond(cur_value_, value);
    cur_value_ = value;

    thumb_->SetPosition({placement_.x0, static_cast<int>((value - range_min_) / GetStep()) + track_.x -
                                                         thumb_->GetHeight() / 2});
}

void VerticalSlider::SetValue(Vec2<int> coordinates)
{
    SetValue((coordinates.y - track_.x) * GetStep());
}
