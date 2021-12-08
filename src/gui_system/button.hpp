#ifndef _BUTTON_HPP_INCLUDED
#define _BUTTON_HPP_INCLUDED

#include "gui_component.hpp"
#include "command.hpp"
#include "icon.hpp"
#include "border.hpp"
#include "../graphics/color.hpp"

class BasicButton : public GUIComponent
{
public:
    BasicButton(const Rectangle& placement, ICommand* command, Texture* texture);
    BasicButton(const Rectangle& placement, ICommand* command, Color bg = kWhite,
                Color border = kBlack);
                
    BasicButton(const Rectangle& placement, ICommand* command, Color bg,
                Color border, Texture* icon);
    BasicButton(const Rectangle& placement, ICommand* command, Color bg, Color border,
                const char* text, Color font_color = kBlack);

    virtual ~BasicButton();

    virtual bool ProcessMouseEvent   (const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;

    void SetRightButtonPressedCommand(ICommand* command);

protected:
    ICommand* command_;
    ICommand* right_button_pressed_;

    bool pressed_;
};

class Button : public BasicButton
{
public:
    Button(const Rectangle& placement, ICommand* command, Texture* on_release,
           Texture* on_press = nullptr, Texture* on_hover = nullptr);
        
    Button(const Rectangle& placement, ICommand* command, Color on_release,
           Color on_press, Color on_hover, const char* text, Color font_color = kBlack);

    Button(const Rectangle& placement, ICommand* command, Color on_release,
           Color on_press, Color on_hover);

    virtual ~Button();
    virtual bool ProcessMouseEvent   (const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;

protected:
    Texture* on_release_;
    Texture* on_press_;
    Texture* on_hover_;
};

class ComponentClose : public ICommand
{
public:
    ComponentClose(GUIComponent* component) : component_(component) {}

    virtual void Execute() override
    {
        EventManager::GetInstance()->PushEvent(Event(kComponentClose, EventValue(component_)));
    }

private:
    GUIComponent* component_;
};

class UnpinComponent : public ICommand
{
public:
    UnpinComponent(GUIComponent* component) : component_(component) {}

    virtual void Execute() override
    {
        GUIComponent* parent = component_->GetParent();
        if (parent != nullptr)
        {
            parent->Detach(component_);
        }
    }

private:
    GUIComponent* component_;
};

#endif /* _BUTTON_HPP_INCLUDED */