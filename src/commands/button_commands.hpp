#ifndef _BUTTON_COMMANDS_HPP_INCLUDED
#define _BUTTON_COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"
#include "../graphics/texture.hpp"

class ButtonOnMouseEvent : public IOnMouseEventCommand
{
public:
    ButtonOnMouseEvent(Texture* texture) : swap_texture_(texture) {}

    ~ButtonOnMouseEvent()
    {
        delete swap_texture_;
    }

    virtual bool Execute(const Event& event) override
    {
        switch (event.GetType())
        {
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