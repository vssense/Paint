#include "api_widgets.hpp"

IButton* APIWidgetFactory::CreateDefaultButtonWithIcon(const char* icon_file_name)
{
    return CreateButtonWithIcon(kDefaultButtonsWidth, kDefaultButtonsHeight, icon_file_name);
}

IButton* APIWidgetFactory::CreateDefaultButtonWithText(const char* text)
{
    return CreateButtonWithText(kDefaultButtonsWidth, kDefaultButtonsHeight, text, 0);
}

IButton* APIWidgetFactory::CreateButtonWithIcon(int32_t width, int32_t height, const char* icon_file_name)
{
    APIClickCallback* callback = new APIClickCallback;
    Button* button = new Button(Rectangle{0, 0, width, height}, callback, new Texture(icon_file_name));

    return new APIButton(button, callback);
}

IButton* APIWidgetFactory::CreateButtonWithText(int32_t width, int32_t height, const char* text,
                                          int32_t char_size)
{
    APIClickCallback* callback = new APIClickCallback;

    Button* button = new Button(Rectangle{0, 0, width, height}, callback,
                                kDefaultOnReleaseColor, kDefaultOnPressColor,
                                kDefaultOnHoverColor, text, kBlack);

    button->AddBorder(kBlack);

    return new APIButton(button, callback);
}


ISlider* APIWidgetFactory::CreateDefaultSlider(float range_min, float range_max)
{
    return CreateSlider(2 * kDefaultButtonsWidth, kDefaultButtonsHeight, range_min, range_max);
}

ISlider* APIWidgetFactory::CreateSlider(int32_t width, int32_t height, float range_min, float range_max)
{
    APISliderCallback* callback = new APISliderCallback; 
    return new APISlider(new HorizontalSlider(Rectangle{0, 0, width, height},
                                              new Texture(width, height, kDefaultOnReleaseColor),
                                              callback, range_min, range_max), callback);
}

ISlider* APIWidgetFactory::CreateSlider(int32_t width, int32_t height, float thumb_width, float thumb_height,
                                  float range_min, float range_max)
{
    return CreateSlider(width, height, range_min, range_max);
}


ILabel* APIWidgetFactory::CreateDefaultLabel(const char* text)
{
    return CreateLabel(kDefaultButtonsWidth, kDefaultButtonsHeight, text, 0);
}

ILabel* APIWidgetFactory::CreateLabel(int32_t width, int32_t height, const char* text, int32_t char_size)
{
    return new APILabel(new Label(Rectangle{0, 0, width, height}, text, kBlack));
}

IPreferencesPanel* APIWidgetFactory::CreateDefaultPreferencesPanel()
{
    return new APIPreferencesPanel(new PreferencesPanel);
}

APIClickCallback::APIClickCallback(IClickCallback* callback)
    : callback_(callback) {}

void APIClickCallback::SetCallback(IClickCallback* callback)
{
    callback_ = callback;
}

void APIClickCallback::Execute()
{
    if (callback_ != nullptr)
    {
        callback_->RespondOnClick();
    }
}

APISliderCallback::APISliderCallback(ISliderCallback* callback)
    : callback_(callback) {}

void APISliderCallback::SetCallback(ISliderCallback* callback)
{
    callback_ = callback;
}

void APISliderCallback::Respond(float old_value, float current_value)
{
    if (callback_ != nullptr)
    {
        callback_->RespondOnSlide(old_value, current_value);
    }
}

APIButton::APIButton(Button* button, APIClickCallback* callback)
    : button_(button), callback_(callback) {}

void APIButton::SetClickCallback(IClickCallback* callback)
{
    callback_->SetCallback(callback);
}

int32_t APIButton::GetWidth()
{
    return button_->GetPlacement().w;
}

int32_t APIButton::GetHeight()
{
    return button_->GetPlacement().h;
}

GUIComponent* APIButton::GetBasicWidget() const
{
    return button_;
}

APISlider::APISlider(HorizontalSlider* slider, APISliderCallback* callback)
    : slider_(slider), callback_(callback) {}

void APISlider::SetSliderCallback(ISliderCallback* callback)
{
    callback_->SetCallback(callback);
}

float APISlider::GetValue()
{
    return slider_->GetValue();
}

void APISlider::SetValue(float value)
{
    slider_->SetValue(value);
}

int32_t APISlider::GetWidth()
{
    return slider_->GetPlacement().w;
}

int32_t APISlider::GetHeight()
{
    return slider_->GetPlacement().h;
}

GUIComponent* APISlider::GetBasicWidget() const
{
    return slider_;
}

APILabel::APILabel(Label* label)
    : label_(label) {}

void APILabel::SetText(const char* text)
{
    label_->SetText(text);
}

int32_t APILabel::GetWidth()
{
    return label_->GetPlacement().w;
}

int32_t APILabel::GetHeight()
{
    return label_->GetPlacement().h;
}

GUIComponent* APILabel::GetBasicWidget() const
{
    return label_;
}

APIPreferencesPanel::APIPreferencesPanel(PreferencesPanel* panel)
    : panel_(panel) {}

void APIPreferencesPanel::Attach(IWidget* widget, int32_t x, int32_t y)
{
    APIWidget* api_widget = dynamic_cast<APIWidget*>(widget);
    panel_->AttachWithCoordinates(api_widget->GetBasicWidget(), Vec2<int32_t>(x, y));
}

int32_t APIPreferencesPanel::GetWidth()
{
    return panel_->GetPlacement().w;
}

int32_t APIPreferencesPanel::GetHeight()
{
    return panel_->GetPlacement().h;
}

GUIComponent* APIPreferencesPanel::GetBasicWidget() const
{
    return panel_;
}
