#ifndef _SLIDER_HPP_INCLUDED
#define _SLIDER_HPP_INCLUDED

#include "gui_component.hpp"

class Slider;

class ISliderResponse
{
public:
    virtual ~ISliderResponse() {}

    virtual void Respond(float old_value, float current_value) = 0;
};

class Thumb : public GUIComponent
{
public:
    Thumb(Vec2<int> size, Texture* texture);
    Thumb(Vec2<int> size);

    int GetWidth() const;
    int GetHeight() const;
    void SetSlider(Slider* slider);
    void SetPosition(Vec2<int> position);
    virtual bool ProcessMouseEvent(const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;

private:
    Slider* slider_;
};

class Slider : public GUIComponent
{
public:
    Slider(const Rectangle& rectangle, Texture* texture, ISliderResponse* callback,
           Thumb* thumb, float range_min = 0, float range_max = 1);

    virtual ~Slider();


    float GetValue() const;
    float GetStep() const;
    int GetTrackStart() const;
    virtual void SetValue(float value) = 0;
    virtual void SetValue(Vec2<int> coordinates) = 0;

protected:
    Thumb* thumb_;
    ISliderResponse* callback_;
    
    float range_min_;
    float range_max_;
    float cur_value_;

    Vec2<int> track_;
};

class HorizontalSlider : public Slider
{
public:
    HorizontalSlider(const Rectangle& rectangle, Texture* texture, ISliderResponse* callback,
                     float range_min = 0, float range_max = 1);
    HorizontalSlider(const Rectangle& rectangle, Texture* texture, ISliderResponse* callback,
                     Thumb* thumb, float range_min = 0, float range_max = 1);

    virtual void Move(Vec2<int> d) override;
    virtual bool ProcessMouseEvent(const Event& event) override;
    virtual void SetValue(float value) override;
    virtual void SetValue(Vec2<int> coordinates) override;
};

class VerticalSlider : public Slider
{
public:
    VerticalSlider(const Rectangle& rectangle, Texture* texture, ISliderResponse* callback,
                   float range_min = 0, float range_max = 1);
    VerticalSlider(const Rectangle& rectangle, Texture* texture, ISliderResponse* callback,
                   Thumb* thumb, float range_min = 0, float range_max = 1);

    virtual void Move(Vec2<int> d) override;
    virtual bool ProcessMouseEvent(const Event& event) override;
    virtual void SetValue(float value) override;
    virtual void SetValue(Vec2<int> coordinates) override;
};

#endif /* _SLIDER_HPP_INCLUDED */
