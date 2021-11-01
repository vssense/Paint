#ifndef _BUTTON_COMMANDS_HPP_INCLUDED
#define _BUTTON_COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"
#include "../graphics/texture.hpp"
#include "canvas_commands.hpp"

class ButtonFileOnMouseEvent : public IOnMouseEventCommand
{
public:
    ButtonFileOnMouseEvent(Texture* texture) : swap_texture_(texture) {}

    ~ButtonFileOnMouseEvent()
    {
        delete swap_texture_;
    }

    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        switch (event.GetType())
        {
            case kMouseButtonRelease:
            {
                printf("File button pressed!\n");
                break;
            }
            case kMouseButtonPress:
            case kMouseButtonOldRelease:
            {
                if (swap_texture_ != nullptr)
                {
                    Texture* tmp = component_->GetTexture();
                    component_->SetTexture(swap_texture_);
                    swap_texture_ = tmp;
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

private:
    Texture* swap_texture_;
};

class ButtonViewOnMouseEvent : public IOnMouseEventCommand
{
public:
    ButtonViewOnMouseEvent(Texture* texture, GUIComponent* main_component) :
        swap_texture_(texture), main_component_(main_component)
    {
        assert(main_component_);
    }

    ~ButtonViewOnMouseEvent()
    {
        delete swap_texture_;
    }

    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        switch (event.GetType())
        {
            case kMouseButtonRelease:
            {
                main_component_->AddChild(CreateCanvas(main_component_->GetRenderer(),
                                                       kDefaultCanvasPlacement));
                break;
            }
            case kMouseButtonPress:
            case kMouseButtonOldRelease:
            {
                if (swap_texture_ != nullptr)
                {
                    Texture* tmp = component_->GetTexture();
                    component_->SetTexture(swap_texture_);
                    swap_texture_ = tmp;
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

private:
    Texture* swap_texture_;
    GUIComponent* main_component_;
};

class ButtonHelpOnMouseEvent : public IOnMouseEventCommand
{
public:
    ButtonHelpOnMouseEvent(Texture* texture) : swap_texture_(texture) {}

    ~ButtonHelpOnMouseEvent()
    {
        delete swap_texture_;
    }

    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        switch (event.GetType())
        {
            case kMouseButtonRelease:
            {
                printf("Help button pressed!\n");
                break;
            }
            case kMouseButtonPress:
            case kMouseButtonOldRelease:
            {
                if (swap_texture_ != nullptr)
                {
                    Texture* tmp = component_->GetTexture();
                    component_->SetTexture(swap_texture_);
                    swap_texture_ = tmp;
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

private:
    Texture* swap_texture_;
};

#endif /* _BUTTON_COMMANDS_HPP_INCLUDED */