#ifndef _API_WIDGETS_HPP_INCLUDED
#define _API_WIDGETS_HPP_INCLUDED

#include "../../plugins/plugin.hpp"
#include "../gui_system/button.hpp"
#include "../gui_system/slider.hpp"
#include "../gui_system/label.hpp"
#include "../paint_gui_components/preferences_panel.hpp"

#define GetHeight GetHieght

using namespace plugin;

const int kDefaultButtonsWidth  = 90;
const int kDefaultButtonsHeight = 30;

const Color kDefaultOnReleaseColor = kLightPurple;
const Color kDefaultOnHoverColor   = kWhite;
const Color kDefaultOnPressColor   = kGray;

class APIWidgetFactory : public IWidgetFactory
{
public:
    APIWidgetFactory() {}

    virtual IButton* CreateDefaultButtonWithIcon(const char* icon_file_name) override;
    virtual IButton* CreateDefaultButtonWithText(const char* text) override;
    virtual IButton* CreateButtonWithIcon(int32_t width, int32_t height, const char* icon_file_name) override;
    virtual IButton* CreateButtonWithText(int32_t width, int32_t height, const char* text,
                                          int32_t char_size) override;

    virtual ISlider* CreateDefaultSlider(float range_min, float range_max) override;
    virtual ISlider* CreateSlider(int32_t width, int32_t height, float range_min, float range_max) override;
    virtual ISlider* CreateSlider(int32_t width, int32_t height, float thumb_width, float thumb_height,
                                  float range_min, float range_max) override;

    virtual ILabel*  CreateDefaultLabel(const char* text) override;
    virtual ILabel*  CreateLabel(int32_t width, int32_t height, const char* text, int32_t char_size) override;

    virtual IPreferencesPanel* CreateDefaultPreferencesPanel() override;
};

class APIClickCallback : public ICommand
{
public:
    APIClickCallback(IClickCallback* callback = nullptr);

    void SetCallback(IClickCallback* callback);

    virtual void Execute() override;

private:
    IClickCallback* callback_;
};

class APISliderCallback : public ISliderResponse
{
public:
    APISliderCallback(ISliderCallback* callback = nullptr);
    
    void SetCallback(ISliderCallback* callback);

    virtual void Respond(float old_value, float current_value) override;


private:
    ISliderCallback* callback_;
};

class APIWidget : public IWidget
{
public:
    virtual GUIComponent* GetBasicWidget() const = 0;
};

class APIButton : public IButton, public APIWidget
{
public:
    APIButton(Button* button, APIClickCallback* callback);
    virtual void SetClickCallback(IClickCallback* callback) override;

    virtual int32_t GetWidth() override;
    virtual int32_t GetHeight() override;

    virtual GUIComponent* GetBasicWidget() const override;

private:
    Button* button_;
    APIClickCallback* callback_;
};

class APISlider : public ISlider, public APIWidget
{
public:
    APISlider(HorizontalSlider* slider, APISliderCallback* callback);
    virtual void SetSliderCallback(ISliderCallback* callback) override;

    virtual float GetValue() override;
    virtual void SetValue(float value) override;

    virtual int32_t GetWidth() override;
    virtual int32_t GetHeight() override;

    virtual GUIComponent* GetBasicWidget() const override;

private:
    HorizontalSlider* slider_;
    APISliderCallback* callback_;
};

class APILabel : public ILabel, public APIWidget
{
public:
    APILabel(Label* label);

    virtual void SetText(const char* text) override;

    virtual int32_t GetWidth() override;
    virtual int32_t GetHeight() override;

    virtual GUIComponent* GetBasicWidget() const override;

private:
    Label* label_;
};

class APIPreferencesPanel : public IPreferencesPanel, public APIWidget
{
public:
    APIPreferencesPanel(PreferencesPanel* panel);
    ~APIPreferencesPanel();

    virtual void Attach(IWidget* widget, int32_t x, int32_t y) override;

    virtual int32_t GetWidth() override;
    virtual int32_t GetHeight() override;

    virtual GUIComponent* GetBasicWidget() const override;

private:
    PreferencesPanel* panel_;
};

#endif /* _API_WIDGETS_HPP_INCLUDED */
