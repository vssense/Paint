#ifndef _CLOSE_COMMANDS_HPP_INCLUDED
#define _CLOSE_COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"
#include "../graphics/texture.hpp"

class MainCloseOnMouseEvent : public IOnMouseEventCommand
{
public:
    MainCloseOnMouseEvent(bool* is_running, const char* path = nullptr,
                          Renderer* renderer = nullptr) :
                          is_running_(is_running), swap_texture_(nullptr)
    {
        assert(is_running_);
        if (path != nullptr && renderer != nullptr)
        {
            swap_texture_ = new Texture(renderer, path);
            assert(swap_texture_);
        }
    }

    ~MainCloseOnMouseEvent()
    {
        delete swap_texture_;
    }

    virtual bool Execute(const Event& event) override
    {
        switch (event.GetType())
        {
            case kMouseButtonRelease:
            {
                *is_running_ = false;
                break;
            }
            case kMouseButtonPress:
            {
                if (swap_texture_ != nullptr)
                {
                    Texture* tmp = component_->GetTexture();
                    component_->SetTexture(swap_texture_);
                    swap_texture_ = tmp;
                }
                break;
            }
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
    bool* is_running_;
    Texture* swap_texture_;
};

#endif /* _CLOSE_COMMANDS_HPP_INCLUDED */
